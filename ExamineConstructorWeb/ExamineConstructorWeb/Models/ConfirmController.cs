using ExamineConstructorWeb.Data;
using Microsoft.EntityFrameworkCore;

namespace ExamineConstructorWeb.Models;

using System.Threading.Tasks;

public interface IConfirmationService
{
    Task<string> GenerateAndSaveCode(int userId);
    Task<bool> VerifyCode(int userId, string code);
}

public class ConfirmController:IConfirmationService
{
    private ApplicationDbContext _context;
    public ConfirmController(ApplicationDbContext context)
    {
        _context = context;
    }
    
    
    public async Task<string> GenerateAndSaveCode(int userId)
    {
        var confirmCode = new Random().Next(100000, 999999).ToString();
        var existingCode = _context.ConfirmCodes.FirstOrDefault(c => c.UserId == userId);

        if (existingCode != null)
        {
            existingCode.Code = confirmCode;
            existingCode.ExpirationTime = DateTime.UtcNow.AddMinutes(5);
        }
        else
        {
            _context.ConfirmCodes.Add(new ConfirmCode
            {
                UserId = userId,
                Code = confirmCode,
                ExpirationTime = DateTime.UtcNow.AddMinutes(5)
            });
        }

        await _context.SaveChangesAsync();
        return confirmCode;
    }
    
    
    public async Task<bool> VerifyCode(int userId, string code)
    {
        var confirmCode = await _context.ConfirmCodes.FirstOrDefaultAsync(c => c.UserId == userId);
        if (confirmCode == null || confirmCode.Code != code || confirmCode.ExpirationTime < DateTime.UtcNow)
            return false;

        _context.ConfirmCodes.Remove(confirmCode);
        await _context.SaveChangesAsync();

        return true;
    }
    
}