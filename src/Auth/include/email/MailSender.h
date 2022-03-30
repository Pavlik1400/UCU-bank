#include <aws/core/Aws.h>
#include <aws/email/SESClient.h>
#include <aws/email/model/SendEmailRequest.h>
#include <aws/email/model/SendEmailResult.h>
#include <aws/email/model/Destination.h>
#include <aws/email/model/Message.h>
#include <aws/email/model/Body.h>
#include <aws/email/model/Content.h>
#include <exception>

namespace email {
    class AWSSessionGuard {
    public:
        AWSSessionGuard() 
        {
            Aws::InitAPI(options_);
        }

        AWSSessionGuard(Aws::SDKOptions&& options) 
            : options_(options)
        {
            Aws::InitAPI(options_);
        }

        ~AWSSessionGuard() {
            Aws::ShutdownAPI(options_);
        }

    private:
        const Aws::SDKOptions options_;
    };


    struct MailInfo {
        std::string sender;
        std::string receiver;
        std::string subject;
        std::string body;
    };


    struct SESService {
        Aws::SES::SESClient client;
        Aws::SES::Model::SendEmailRequest request;
    };


    class MailSender {
    public:
        MailSender& with_receiver(const std::string& receiver);
        MailSender& with_sender(const std::string& sender);
        MailSender& with_subject(const std::string& subject);
        MailSender& with_body(const std::string& body);
        void send(void) noexcept(false);

    private: 
        AWSSessionGuard session_; // Initialize and cleans SDK
        SESService ses_;
        MailInfo minfo_; 

        Aws::SES::Model::Destination get_receiver__(void);
        Aws::SES::Model::Content get_subject__(void);
        Aws::SES::Model::Body get_body__(void); 
        void set_req__(void);
    };
}