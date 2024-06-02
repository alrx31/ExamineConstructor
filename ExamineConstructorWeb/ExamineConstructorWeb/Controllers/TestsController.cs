using ExamineConstructorWeb.Data;
using ExamineConstructorWeb.Models;
using Microsoft.AspNetCore.Mvc;
using Microsoft.EntityFrameworkCore;

namespace ExamineConstructorWeb.Controllers
{
    [Route("api/[controller]")]
    [ApiController]
    public class TestsController : ControllerBase
    {
        private readonly ApplicationDbContext _context;
        public TestsController(ApplicationDbContext context)
        {
            _context = context;
        }

        [HttpGet]
        public IActionResult GetAllTests()
        {
            var len = _context.Tests.Count();
            if (len == 0) return BadRequest();
            return Ok(_context.Tests.ToList());
        }
    
        

        [HttpDelete]
        public IActionResult DeleteTest(int id)
        {
            var test = _context.Tests.Find(id);
            if (test == null) return BadRequest();
            _context.Tests.Remove(test);
            _context.SaveChanges();
            return Ok();
        }

        [HttpGet("getmytest")]
        public IActionResult GetMyTests(int id)
        {
            var tests = _context.Tests.Where(t => t.AuthorId == id).ToList();
            if (!tests.Any()) return BadRequest();
            return Ok(tests);
        }
    
        private int getLastTestId()
        {
            return _context.Tests.Any() ? _context.Tests.Max(t => t.Id) : 0;
        }

        private int getLastQuesStId()
        {
            return _context.Questions_standart.Any() ? _context.Questions_standart.Max(q => q.Id) : 0;
        }
    
        private int getLastRaitingId()
        {
            return _context.Raiting.Any() ? _context.Raiting.Max(r => r.Id) : 0;
        }
    }
}
