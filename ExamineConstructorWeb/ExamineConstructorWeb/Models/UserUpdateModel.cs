namespace ExamineConstructorWeb.Models;

public class UserUpdateModel
{
    public int ID { get; set; }
    public string Login { get; set; }
    public string Password { get; set; }
    public string Surname { get; set; }
    public string Name { get; set; }
    public string Email { get; set; }
    public int Age { get; set; }
    public int RuleLevel { get; set; }
    public string ConfirmCode { get; set; }
}