#include "auth/service.hpp"
#include "notification/email/MailSender.h"
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
   user::Client("bin-user", 54321).create(mak9su4roi);

    return 0;
}