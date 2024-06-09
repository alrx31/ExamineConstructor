using Microsoft.EntityFrameworkCore;
using ExamineConstructorWeb.Models;

namespace ExamineConstructorWeb.Data
{
    public class ApplicationDbContext : DbContext
    {
        public ApplicationDbContext(DbContextOptions<ApplicationDbContext> options) : base(options)
        {
        }

        public DbSet<UserModel> Users { get; set; }
        public DbSet<TestModel> Tests { get; set; }
        public DbSet<Question_st_Model> Questions_standart { get; set; }
        public DbSet<RaitingModel> Raiting { get; set; }
        public DbSet<ConfirmCode> ConfirmCodes { get; set; }
    }
}