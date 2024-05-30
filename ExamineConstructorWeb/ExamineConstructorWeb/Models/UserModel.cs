using System.ComponentModel.DataAnnotations;

namespace ExamineConstructorWeb.Models;

public class UserModel
{
    [Key]
    public int ID { get; set; }
    [Required]
    public string Login { get; set; }
    [Required]
    public string Password { get; set; }
    [Required]
    public string Surname { get; set; }
    [Required]
    public string Name { get; set; }
    [Required]
    [EmailAddress]
    public string Email { get; set; }
    [Required]
    public int Age { get; set; }
    [Required]
    public int RuleLevel { get; set; }
}