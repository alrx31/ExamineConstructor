using ExamineConstructorWeb.Data;
using ExamineConstructorWeb.Models;
using Microsoft.AspNetCore.Mvc;

namespace ExamineConstructorWeb.Controllers;


[Route("api/[controller]")]
[ApiController]
public class LoginController: ControllerBase
{
    private readonly ApplicationDbContext _context;
    public LoginController(ApplicationDbContext context)
    {
        _context = context;
    }
        
    [HttpPost]
    public IActionResult Login([FromBody] LoginModel model)
    {
        if (ModelState.IsValid)
        {
            model.Password = GetHash(model.Password);
            var user = _context.Users.FirstOrDefault(u => u.Login == model.Login && u.Password == model.Password);
            if (user != null)
            {
                return Ok(user);
            }
            return BadRequest(new {message = "Authorization failed", model});
        }

        return BadRequest(ModelState);
    }
    private string GetHash(string pass)
    {
        var data = System.Text.Encoding.ASCII.GetBytes(pass);
        data = new System.Security.Cryptography.SHA256Managed().ComputeHash(data);
        return System.Text.Encoding.ASCII.GetString(data);
    }
}