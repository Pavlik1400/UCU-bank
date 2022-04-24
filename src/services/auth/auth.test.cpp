#include "auth/service.hpp"
#include "email/MailSender.h"
#include <iostream>
#include "user/client.h"
#include "service_tools/utils.hpp"


int main() {
    user_t mak9su4roi{
        .id="1234567890",
        .type="public",
        .name="Makkusu Shiroi",
        .password="0000",
        .date_of_birth="17.01.2002",
        .phoneNo="+380(xx)xxxxx",
        .email="makkusu.shiroi@gmail.com",
        .address="Lviv, Ukraine",
        .gender="male",
        .joining_date="01.01.2022"
    };
    user::Client("127.0.0.1", 45646).create(mak9su4roi);
// 
    // email::MailSender sender;
// 
    // try {
        // sender.with_sender("ucu.bank.24@gmail.com")
            // .with_receiver("ucu.bank.2022@gmail.com")
            // .with_subject("Authentication")
            // .with_body("Secret_password_0")
            // .send();
        // sender.with_body("Secret_password_1").send();
        // sender.with_receiver("wrong").send();
    // }
    // catch (std::exception& e) {
        // std::cerr << e.what() << std::endl;
    // }
    return 0;
}