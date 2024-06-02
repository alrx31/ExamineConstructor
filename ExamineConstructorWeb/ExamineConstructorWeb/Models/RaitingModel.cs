using System.ComponentModel.DataAnnotations;

namespace ExamineConstructorWeb.Models;

public class RaitingModel
{
    [Key]
    public int Id { get; set; }
    [Required]
    public int UserId { get; set; }
    public UserModel User { get; set; }
    [Required]
    public int Score { get; set; }
    [Required]
    public int TestId { get; set; }
    public TestModel Test { get; set; }
}