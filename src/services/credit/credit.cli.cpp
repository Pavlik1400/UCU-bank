#include "credit/client.h"
#include "account//client.h"
#include "service_tools/utils.hpp"
#include "user/constants.h"


int main() {
    auto cnf = load_json_config("./configs/main.json");
    auto client = credit::Client{cnf["credit"]["rpc_address"].get<std::string>(),
                                  cnf["credit"]["rpc_port"].get<int>()};
    auto account_client = account::Client{cnf["account"]["rpc_address"].get<std::string>(),
                                 cnf["account"]["rpc_port"].get<int>()};

    auto[status_acc1, acc1] = account_client.get("6390721926535760", {.data=user::privilege::SUPER});
    std::cout << "Account: " << acc1 << std::endl << std::endl;

    client.create("62656029a1ad40290a36da63", "6390721926535760", 0, 140.2, {.data=user::privilege::SUPER});

    auto[status_acc2, acc2] = account_client.get("6390721926535760", {.data=user::privilege::SUPER});
    std::cout << "Account with credit: " << acc2 << std::endl << std::endl;

    auto[status, credits] = client.get_all("62656029a1ad40290a36da63", {.data=user::privilege::SUPER});

    for (auto& credit_: credits) {
        std::cout << "Credit: " << credit_ << std::endl;
    }

//    client.finish_credit("62656029a1ad40290a36da63", credits[0].id, {.data=user::privilege::SUPER});
//
//    auto[status_acc3, acc3] = account_client.get("6390721926535760", {.data=user::privilege::SUPER});
//    std::cout << "Account after finish: " << acc3 << std::endl << std::endl;
//
//    auto[status1, credits1] = client.get_all("62656029a1ad40290a36da63", {.data=user::privilege::SUPER});
//
//    for (auto& credit_: credits1) {
//        std::cout << "Credit: " << credit_ << std::endl;
//    }
}