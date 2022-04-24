#include "email/MailSender.h"

namespace email {
    MailSender& MailSender::with_receiver(const std::string& receiver)
    {
        minfo_.receiver = receiver;
        return *this;
    }

    MailSender& MailSender::with_sender(const std::string& sender)
    {
        minfo_.sender = sender;
        return *this;
    }

    MailSender& MailSender::with_subject(const std::string& subject)
    {
        minfo_.subject = subject;
        return *this;
    }

    MailSender& MailSender::with_body(const std::string& body)
    {
        minfo_.body = body;
        return *this;
    }

    void MailSender::send(void) noexcept(false)
    {
        if ( session_ ) {
            set_req__();
            auto ses_res = ses_->client.SendEmail(ses_->request);

            if ( false == ses_res.IsSuccess() )
                throw std::runtime_error("Error" + ses_res.GetError().GetMessage());
        } else {
            std::cout << "MOCK" << std::endl;
        }
    }

    Aws::SES::Model::Destination MailSender::get_receiver__(void)
    {
        return Aws::SES::Model::Destination()
            .WithToAddresses({minfo_.receiver});
    }

    Aws::SES::Model::Content MailSender::get_subject__(void)
    {
        return Aws::SES::Model::Content()
            .WithData(minfo_.subject.c_str())
            .WithCharset("UTF-8");
    }

    Aws::SES::Model::Body MailSender::get_body__(void)
    {
    return Aws::SES::Model::Body()
            .WithText(
                Aws::SES::Model::Content()
                .WithData(minfo_.body.c_str())
                .WithCharset("UTF-8")
            );
    }

    void MailSender::set_req__(void)
    {
    ses_->request.WithSource(minfo_.sender.c_str())
                .WithDestination(get_receiver__())
                .WithMessage(
                    Aws::SES::Model::Message()
                    .WithSubject(get_subject__())
                    .WithBody(get_body__())
                );
    }
}