using ExamineConstructorWeb.Data;
using ExamineConstructorWeb.Models;
using Microsoft.AspNetCore.Authorization;
using Microsoft.AspNetCore.Mvc;


namespace ExamineConstructorWeb.Controllers;
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
        public IActionResult  GetAllTests()
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

        [HttpGet("test/{Testid}")]
        public IActionResult GetTest(int Testid)
        {
            var test = _context.Tests.FirstOrDefault(t => t.Id == Testid);
            if (test == null) return BadRequest();
            var questions = _context.Questions_standart.Where(q => q.TestId == test.Id).ToArray();
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
                Id = test.Id,
                Name = test.Name,
                Description = test.Description,
                AuthorId = test.AuthorId,
                Difficulty = test.Difficulty,
                questions_St = quests.ToArray()
            };
            return Ok(Test);
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
        [Authorize]
        [HttpPut("update/{id}")]
        public IActionResult UpdateTest(int id, [FromBody] TestAddModel model)
        {
            if (!ModelState.IsValid) return BadRequest();
            var test = _context.Tests.FirstOrDefault(t => t.Id == id);
            if (test == null) return BadRequest();
            if (model.Name != "") test.Name = model.Name;
            if (model.Description != "") test.Description = model.Description;
            if (model.Difficulty != 0) test.Difficulty = model.Difficulty;
            _context.Tests.Update(test);
            _context.SaveChanges();
            //update questions and create if not exist
            var lastQId = getLastQuesStId() + 1;
            for(int i = 0 ; i < model.questions_St.Length; i++)
            {
                var quest = _context.Questions_standart.FirstOrDefault(q => q.Id == model.questions_St[i].Id);
                if (quest == null)
                {
                    var newQuest = new Question_st_Model
                    {
                        Id = lastQId + i,
                        Question = model.questions_St[i].Question,
                        Answer = model.questions_St[i].Answer,
                        Difficulty = model.questions_St[i].Difficulty,
                        TestId = test.Id
                    };
                    _context.Questions_standart.Add(newQuest);
                }
                else
                {
                    if (model.questions_St[i].Question != "") quest.Question = model.questions_St[i].Question;
                    if (model.questions_St[i].Answer != "") quest.Answer = model.questions_St[i].Answer;
                    if (model.questions_St[i].Difficulty != 0) quest.Difficulty = model.questions_St[i].Difficulty;
                    _context.Questions_standart.Update(quest);
                }
            }
            
            
            //delete raitings
            var raitings = _context.Raiting.Where(r => r.TestId == test.Id).ToArray();
            foreach (var r in raitings)
            {
                _context.Raiting.Remove(r);
            }
            _context.SaveChanges();
            
            return Ok();
        }
        [Authorize]
        [HttpPost("check")]
        public IActionResult CheckResult([FromBody] TestToPassModel model)
        {
            if(!ModelState.IsValid) return BadRequest( new {message = "Invalid"});
            var Result = new RaitingAddModel
            {
                UserId = model.UserId,
                TestId = model.TestId,
                Score = 0,
            };
            foreach (var que in model.questions_St)
            {
                var rightque = _context.Questions_standart.FirstOrDefault(q => q.Id == que.Id);
                if (rightque.Answer.ToLower().Trim() == que.Answer.ToLower().Trim())
                {
                    Result.Score += que.Difficulty;
                } 
            }
            Result.Score = Result.Score % 100;
            var Raiting = new RaitingModel
            {
                Id = getLastRaitingId() + 1,
                UserId = Result.UserId,
                TestId = Result.TestId,
                Score = Result.Score
            };
            _context.Raiting.Add(Raiting);
            _context.SaveChanges();
            return Ok(Raiting);
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

