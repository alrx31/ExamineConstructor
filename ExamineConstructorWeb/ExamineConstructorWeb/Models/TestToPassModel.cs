namespace ExamineConstructorWeb.Models;

public class TestToPassModel
{
    public int TestId { get; set; }
    public int UserId { get; set; }
    public int Difficulty { get; set; }
    public PassQueModel[] questions_St { get; set; }
}