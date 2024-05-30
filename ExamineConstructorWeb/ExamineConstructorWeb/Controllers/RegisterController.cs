using ExamineConstructorWeb.Data;
using ExamineConstructorWeb.Models;
using Microsoft.AspNetCore.Mvc;

namespace ExamineConstructorWeb.Controllers;

[Route("api/[controller]")]
[ApiController]

public class RegisterController : ControllerBase
{
    private readonly ApplicationDbContext _context;
    public RegisterController(ApplicationDbContext context)
    {
        _context = context;
    }
    [HttpPost]
    public IActionResult Register([FromBody] UserModel model)
    {
        if (ModelState.IsValid)
        {
            _context.Users.Add(model);
            _context.SaveChanges();
            Console.WriteLine($"Login: {model.Login}, Password: {model.Password}");
            return Ok(new {message = "Register successful"});
        }

        return BadRequest(ModelState);
    }
}