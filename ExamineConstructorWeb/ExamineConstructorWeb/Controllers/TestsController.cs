using ExamineConstructorWeb.Data;
using ExamineConstructorWeb.Models;
using Microsoft.AspNetCore.Mvc;


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

        [HttpGet("tests")]
        public IActionResult GetAllTests()
        {
            if ( !_context.Tests.Any()) return BadRequest();
            List<TestModel> tests = _context.Tests.ToList();
            List<TestAddModel> testsExport = [];
            foreach (var t in tests)
            {
                var questions = _context.Questions_standart.Where(q => q.TestId == t.Id).ToArray();
                List<AddQueModel> quests = [];
                foreach (var q in questions)
                {
                    var que = new AddQueModel
                    {
                        Id = q.Id,
                        Question = q.Question,
                        Answer = q.Answer,
                        Difficulty = q.Difficulty,
                    };
                    quests.Add(que);
                }
                var Test = new TestAddModel
                {
                    Id = t.Id,
                    Name = t.Name,
                    Description = t.Description,
                    AuthorId = t.AuthorId,
                    Difficulty = t.Difficulty,
                    questions_St = quests.ToArray()
                };
                testsExport.Add(Test);
            }
            
            
            return Ok(testsExport);
        }

        [HttpPut("addtest")]
        public IActionResult AddTest([FromBody] TestAddModel model)
        {
            if (!ModelState.IsValid) return BadRequest();
            var test = new TestModel
            {
                Id = getLastTestId() + 1,
                Name = model.Name,
                Description = model.Description,
                AuthorId = model.AuthorId,
                Difficulty = model.Difficulty,
                Duration = 0
            };

            _context.Tests.Add(test);
            _context.SaveChanges();

            var lastQId = getLastQuesStId() + 1;
            for(int i = 0 ; i < model.questions_St.Length; i++)
            {
                var quest = new Question_st_Model
                {
                    Id = lastQId + i,
                    Question = model.questions_St[i].Question,
                    Answer = model.questions_St[i].Answer,
                    Difficulty = model.questions_St[i].Difficulty,
                    TestId = test.Id
                    
                };
                _context.Questions_standart.Add(quest);
            }

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

        
        [HttpDelete("{id}")]
        public IActionResult DeleteTest(int id)
        {
            var test = _context.Tests.FirstOrDefault(t => t.Id == id);
            if (test == null) return BadRequest();
            _context.Tests.Remove(test);
            _context.SaveChanges();
            return Ok();
        }
        
        [HttpPut("update/{id}")]
        public IActionResult UpdateTest(int id, [FromBody] TestModel model)
        {
            if (!ModelState.IsValid) return BadRequest();
            var test = _context.Tests.FirstOrDefault(t => t.Id == id);
            if (test == null) return BadRequest();
            if (model.Name != "") test.Name = model.Name;
            if (model.Description != "") test.Description = model.Description;
            if (model.Difficulty != 0) test.Difficulty = model.Difficulty;
            _context.SaveChanges();
            return Ok();
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
