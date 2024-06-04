using ExamineConstructorWeb.Data;
using ExamineConstructorWeb.Models;
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

    [HttpGet("{TestId}")]
    public IActionResult GetTestRaiting(int TestId)
    {
        var raitings = _context.Raiting.Where(r => r.TestId == TestId).ToList();
        return Ok(raitings);
    }
    
    [HttpPut("add")]
    public IActionResult AddRaiting([FromBody] RaitingAddModel model)
    {
        if (!ModelState.IsValid) return BadRequest();
        var raiting = new RaitingModel
        {
            Id = getLastRaitingId()+1,
            UserId = model.UserId,
            Score = model.Score,
            TestId = model.TestId,
        };
        _context.Raiting.Add(raiting);
        _context.SaveChanges();
        return Ok();
    }
    
    [HttpDelete("delete/{RaitingId}")]
    public IActionResult DeleteRaiting(int RaitingId)
    {
        var raiting = _context.Raiting.FirstOrDefault(r => r.Id == RaitingId);
        if (raiting == null) return BadRequest();
        _context.Raiting.Remove(raiting);
        _context.SaveChanges();
        return Ok();
    }
    
    
    private int getLastRaitingId()
    {
        return _context.Raiting.Any() ? _context.Raiting.Max(r => r.Id) : 0;
    }
    
}