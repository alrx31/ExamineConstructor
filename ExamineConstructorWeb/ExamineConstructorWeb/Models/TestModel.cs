using System.ComponentModel.DataAnnotations;

namespace ExamineConstructorWeb.Models;

public class TestModel
{
    [Key]
    public int Id { get; set; }
    [Required]
    public string Name { get; set; }
    [Required]
    public string Description { get; set; }
    public UserModel Author { get; set; }
    [Required]
    public int AuthorId { get; set; }
    [Required]
    public int Difficulty { get; set; }
    [Required]
    public int Duration { get; set; }
}