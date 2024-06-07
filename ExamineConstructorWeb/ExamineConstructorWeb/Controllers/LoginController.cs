using System.IdentityModel.Tokens.Jwt;
using System.Security.Claims;
using System.Text;
using ExamineConstructorWeb.Data;
using ExamineConstructorWeb.Models;
using Microsoft.AspNetCore.Authorization;
using Microsoft.AspNetCore.Mvc;
using Microsoft.IdentityModel.Tokens;

namespace ExamineConstructorWeb.Controllers;


[Route("api/[controller]")]
[ApiController]
public class LoginController: ControllerBase
{
    private readonly ApplicationDbContext _context;
    private readonly string _key;
    public LoginController(ApplicationDbContext context,IConfiguration config)
    {
        _context = context;
        _key = config["Jwt:Key"];
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
                var token = GenerateJwtToken(user);
                return Ok(new 
                { 
                    token,
                    user = new 
                    {
                        user.ID,
                        user.Name,
                        user.Surname,
                        user.Email,
                        user.Age,
                        user.Login,
                        user.Password,
                        user.RuleLevel
                    }
                });
            }
            return BadRequest(new {message = "Authorization failed"});
        }

        return BadRequest(ModelState);
    }

    [HttpPost("validate-token")]
    public IActionResult ValidateToken()
    {
        var userId = User.Claims.FirstOrDefault(c => c.Type == "id")?.Value;
        if (userId == null)
        {
            return Unauthorized();
        }
        var user = _context.Users.FirstOrDefault(u=> u.ID == int.Parse(userId));
        if (user == null)
        {
            return Unauthorized();
        }

        return Ok(user);
    }
    

    private string GetHash(string pass)
    
    {
        var data = System.Text.Encoding.ASCII.GetBytes(pass);
        data = new System.Security.Cryptography.SHA256Managed().ComputeHash(data);
        return Encoding.ASCII.GetString(data);
    }
    
    
    private string GenerateJwtToken(UserModel user){
        var tokenHandler = new JwtSecurityTokenHandler();
        var key = Encoding.ASCII.GetBytes(_key);
        var tokenDescriptor = new SecurityTokenDescriptor()
        {
            Subject = new ClaimsIdentity(new[] { new Claim("id", user.ID.ToString()) }),
            Expires = DateTime.UtcNow.AddSeconds(10),
            SigningCredentials =
                new SigningCredentials(new SymmetricSecurityKey(key), SecurityAlgorithms.HmacSha256Signature)
        };
        var token = tokenHandler.CreateToken(tokenDescriptor);
        return tokenHandler.WriteToken(token);
    }
    
    
}