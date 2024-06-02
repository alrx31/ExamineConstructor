namespace ExamineConstructorWeb.Models;

public class TestAddModel
{
    public int Id { get; set; }
    public string Name { get; set; }
    public string Description { get; set; }
    public int AuthorId { get; set; }
    public int Difficulty { get; set; }
    public AddQueModel[] questions_St { get; set; }
}