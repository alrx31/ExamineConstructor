using ExamineConstructorWeb.Data;
using ExamineConstructorWeb.Models;
using Microsoft.AspNetCore.Mvc;

namespace ExamineConstructorWeb.Controllers;


[Route("api/[controller]")]
[ApiController]
public class ExportController:ControllerBase
{
    private readonly ApplicationDbContext _context;
    
    public ExportController(ApplicationDbContext context)
    {
        _context = context;
    }
    
    /*// create file
    [HttpGet("{TestId}")]
    public async Task<IActionResult> Post(int TestId)
    {
        var model = _context.Tests.FirstOrDefault(t => t.Id == TestId);
        string path =  "export/" + model.Id + ".txt";
        var questions = _context.Questions_standart.Where(q=>q.TestId == model.Id).ToList();
        using (StreamWriter writer = new StreamWriter(path))
        {
            writer.WriteLine("Название теста: " + model.Name);
            writer.WriteLine("Описание: "+ model.Description);
            writer.WriteLine("Сложность: " + model.Difficulty);
            writer.WriteLine("Автор: " + model.Author.Name);
            writer.WriteLine("Вопросы: ");
            var i = 1;
            foreach (var que in questions)
            {
                writer.WriteLine("Вопрос "+ i++ + ": " + que.Question);
                writer.WriteLine("Сложность: "+ que.Difficulty);
            }
    
        }

        return Ok(path);
    } */
}