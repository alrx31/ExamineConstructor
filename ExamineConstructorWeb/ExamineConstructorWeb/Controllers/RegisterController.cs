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
            // хеширования пароля
            model.Password = model.Password.GetHashCode().ToString();
            
            var userCheck = _context.Users.FirstOrDefault(u => u.Login == model.Login);
            if(userCheck != null)
            {
                return BadRequest(new {message = "User with this login already exists", code="login"});
            }
            _context.Users.Add(model);
            _context.SaveChanges();
            return Ok(new {message = "Register successful"});
        }

        return BadRequest(ModelState);
    }
}