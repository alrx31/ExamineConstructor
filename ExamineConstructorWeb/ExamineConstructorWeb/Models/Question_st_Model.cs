using System.ComponentModel.DataAnnotations;

namespace ExamineConstructorWeb.Models;

public class Question_st_Model
{
    [Key]
    public int Id { get; set; }
    [Required]
    public string Question { get; set; }
    [Required]
    public string Answer { get; set; }
    [Required]
    public int Difficulty { get; set; }
    [Required]
    public int TestId { get; set; }
    public TestModel Test { get; set; }
}