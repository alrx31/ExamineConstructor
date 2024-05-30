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
    }
}