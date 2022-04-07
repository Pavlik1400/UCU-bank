#include "email/MailSender.h"
#include <iostream>

int main(void) {
    email::MailSender sender;
    
    try {
        sender.with_sender("ucu.bank.24@gmail.com")
            .with_receiver("ucu.bank.2022@gmail.com")
            .with_subject("Authentication")
            .with_body("Secret_password_0")
            .send();
        sender.with_body("Secret_password_1").send();
        sender.with_receiver("wrong").send();
    }
    catch (std::exception& e) {
        std::cerr << e.what() << std::endl;
    }
    return 0;
}