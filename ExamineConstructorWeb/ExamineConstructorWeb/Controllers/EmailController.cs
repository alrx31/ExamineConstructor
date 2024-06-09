using ExamineConstructorWeb.Models;

namespace ExamineConstructorWeb.Controllers;

using Microsoft.AspNetCore.Mvc;
using System.Threading.Tasks;

[Route("api/[controller]")]
[ApiController]
public class EmailController : ControllerBase
{
    private readonly IEmailSender _emailSender;

    public EmailController(IEmailSender emailSender)
    {
        _emailSender = emailSender;
    }

    [HttpPut("send")]
    public async Task<IActionResult> Send([FromBody] EmailModel model)
    {
        if (!ModelState.IsValid) return BadRequest();
        await _emailSender.SendEmail(model.Email, model.Subject, model.Message);
        return Ok();
    }
}
