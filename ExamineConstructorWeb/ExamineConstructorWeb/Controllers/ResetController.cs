using ExamineConstructorWeb.Data;
using ExamineConstructorWeb.Models;
using Microsoft.AspNetCore.Authorization;
using Microsoft.AspNetCore.Mvc;
namespace ExamineConstructorWeb.Controllers;



[Route("api/[controller]")]
[ApiController]
public class ResetController:ControllerBase
{
    private readonly IEmailSender _emailSender;
    private readonly ApplicationDbContext _context;
    private readonly IConfirmationService _confirmationService;
    
    public ResetController(IEmailSender emailSender, ApplicationDbContext context, IConfirmationService confirmationService)
    {
        _emailSender = emailSender;
        _context = context;
        _confirmationService = confirmationService;
    }
    
    [HttpPost("reset-request")]
    public async Task<IActionResult> ResetProfile([FromBody] EmailModel model)
    {
        if (!ModelState.IsValid) return BadRequest();
        var user = _context.Users.FirstOrDefault(u => u.Email == model.Email);
        if (user == null) return NotFound("User not found");

        var confirmCode = await _confirmationService.GenerateAndSaveCode(user.ID);
        await _emailSender.SendEmail(model.Email, "Запрос на редактирование", $"Ваш код подтверждения: {confirmCode}");

        return Ok();
    }

    [HttpPost("reset")]
    [Authorize]
    public async Task<IActionResult> ResetProfile([FromBody] UserUpdateModel model)
    {
        if (!ModelState.IsValid) return BadRequest();

        var user = _context.Users.FirstOrDefault(u => u.Email == model.Email);
        if (user == null) return NotFound("User not found");

        var isValidCode = await _confirmationService.VerifyCode(user.ID, model.ConfirmCode);
        if (!isValidCode) return BadRequest("Invalid code");

        user.Login = model.Login;
        user.Password = model.Password;
        user.Surname = model.Surname;
        user.Name = model.Name;
        user.Age = model.Age;
        user.RuleLevel = model.RuleLevel;

        await _context.SaveChangesAsync();
        return Ok("Profile updated successfully.");
    }
    
}