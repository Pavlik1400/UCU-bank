#pragma once

#include <aws/core/Aws.h>
#include <aws/email/SESClient.h>
#include <aws/email/model/SendEmailRequest.h>
#include <aws/email/model/SendEmailResult.h>
#include <aws/email/model/Destination.h>
#include <aws/email/model/Message.h>
#include <aws/email/model/Body.h>
#include <aws/email/model/Content.h>
#include <exception>
#include <optional>

namespace email {
    class AWSSessionGuard {
    public:
        AWSSessionGuard()
        {
            Aws::InitAPI(options_);
            std::cerr << "INIT" << std::endl;
        }

        explicit AWSSessionGuard(Aws::SDKOptions && options)
            : options_(options)
        {
            Aws::InitAPI(options_);
        }

        ~AWSSessionGuard() {
            Aws::ShutdownAPI(options_);
            std::cerr << "DINIT";
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
        explicit MailSender(bool mock)
        : session_{mock? std::optional<AWSSessionGuard>(): std::make_optional<AWSSessionGuard>()}
        , ses_{mock? std::optional<SESService>(): std::make_optional<SESService>()}
        {};
        
        MailSender& with_receiver(const std::string& receiver);
        MailSender& with_sender(const std::string& sender);
        MailSender& with_subject(const std::string& subject);
        MailSender& with_body(const std::string& body);
        void send() noexcept(false);

    private: 
        std::optional<AWSSessionGuard> session_; // Initialize and cleans SDK
        std::optional<SESService> ses_;
        MailInfo minfo_; 

        Aws::SES::Model::Destination get_receiver_();
        Aws::SES::Model::Content get_subject_() const;
        Aws::SES::Model::Body get_body_() const;
        void set_req_();
    };
}