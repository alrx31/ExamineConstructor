using System.ComponentModel.DataAnnotations;

namespace ExamineConstructorWeb.Models;

public class ConfirmCode
{
        
        [Key]
        public int Id { get; set; }
        public UserModel User { get; set; }
        [Required]
        public int UserId { get; set; }
        [Required]
        public string Code { get; set; }
        [Required]
        public DateTime ExpirationTime { get; set; }
}
