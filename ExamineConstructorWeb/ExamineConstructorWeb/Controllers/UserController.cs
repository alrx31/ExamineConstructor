using ExamineConstructorWeb.Data;
using ExamineConstructorWeb.Models;
using Microsoft.AspNetCore.Mvc;

namespace ExamineConstructorWeb.Controllers;


[Route("api/[controller]")]
[ApiController]
public class UserController:ControllerBase
{
    private readonly ApplicationDbContext _context;
    public UserController(ApplicationDbContext context)
    {
        _context = context;
    }
    
    [HttpDelete("{UserId}")]
    public IActionResult DeleteUser(int UserId)
    {
        var user = _context.Users.FirstOrDefault(u => u.ID == UserId);
        if (user == null) return BadRequest();
        _context.Users.Remove(user);
        _context.SaveChanges();
        return Ok();
    }
    [HttpPut("changeLevel/{UserId}/{Level}")]
    public IActionResult ChangeUserLevel(int UserId, int Level)
    {
        var user = _context.Users.FirstOrDefault(u => u.ID == UserId);
        if (user == null) return BadRequest();
        user.RuleLevel = Level;
        _context.SaveChanges();
        return Ok();
    }
    [HttpPut("update/{UserId}")]
    public IActionResult UpdateUser(int UserId, [FromBody] UserModel model)
    {
        if (!ModelState.IsValid) return BadRequest();
        var user = _context.Users.FirstOrDefault(u => u.ID == UserId);
        if (user == null) return BadRequest();
        if(model.Name != "") user.Name = model.Name;
        if(model.Surname != "") user.Surname = model.Surname;
        if(model.Email != "") user.Email = model.Email;
        if(model.Password != "") user.Password = model.Password;
        
        _context.SaveChanges();
        return Ok();
    }
    

}