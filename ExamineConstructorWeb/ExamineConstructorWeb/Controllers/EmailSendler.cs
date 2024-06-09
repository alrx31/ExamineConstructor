using System.Net;
using System.Net.Mail;
using System.Threading.Tasks;
using ExamineConstructorWeb.Models;
using Microsoft.Extensions.Options;

public interface IEmailSender
{
    Task SendEmail(string email, string subject, string message);
}

public class EmailSender : IEmailSender
{
    private readonly SmtpSettings _smtpSettings;

    public EmailSender(IOptions<SmtpSettings> smtpSettings)
    {
        _smtpSettings = smtpSettings.Value;
    }

    public async Task SendEmail(string email, string subject, string message)
    {
        var mailMessage = new MailMessage
        {
            From = new MailAddress(_smtpSettings.SenderEmail, _smtpSettings.SenderName),
            Subject = subject,
            Body = message,
            IsBodyHtml = false
        };
        mailMessage.To.Add(email);

        using (var client = new SmtpClient(_smtpSettings.Server, _smtpSettings.Port))
        {
            client.Credentials = new NetworkCredential(_smtpSettings.Username, _smtpSettings.Password);
            client.EnableSsl = true;
            await client.SendMailAsync(mailMessage);
        }
    }
}