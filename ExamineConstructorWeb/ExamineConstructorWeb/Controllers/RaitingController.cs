using ExamineConstructorWeb.Data;
using Microsoft.AspNetCore.Mvc;

namespace ExamineConstructorWeb.Controllers;


[Route("api/[controller]")]
[ApiController]

public class RaitingController:ControllerBase
{
    private readonly ApplicationDbContext _context;
    public RaitingController(ApplicationDbContext context)
    {
        _context = context;
    }

    [HttpGet]
    public IActionResult GetTestRaiting(int TestId)
    {
        var raitings = _context.Raiting.Where(r => r.TestId == TestId).ToList();
        if(raitings.Count == 0) return BadRequest();
        return Ok(raitings);
    }
}