#include "user/client.h"
#include "service_tools/utils.hpp"


int main() {
    auto cnf = load_json_config("./configs/main.json");


    auto client = user::Client{cnf["user"]["rpc_address"].get<std::string>(),
                                  cnf["user"]["rpc_port"].get<int>()};

    user_t mak9su4roi{
            .id="1234567890",
            .type="public",
            .name="Bankrot",
            .password="0000",
            .date_of_birth="17.01.2002",
            .phoneNo="+380(98)3928392",
            .email="bankrot@gmail.com",
            .address="Lviv, Ukraine",
            .gender="male",
            .joining_date="01.01.2022"
    };
//    std::cout << user::status_to_str(client.create(mak9su4roi)) << std::endl;

//    std::cout << user::status_to_str(client.valid_password(mak9su4roi.phoneNo, mak9su4roi.password)) << std::endl;
    std::cout << client.get<user::by::ID>("625fbadb4baea65e95093e92").second << std::endl;

}