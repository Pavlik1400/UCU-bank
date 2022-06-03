#include "transaction/client.hpp"
#include "service_tools/utils.hpp"
#include <iostream>
#include "user/constants.h"


int main() {
    auto cnf = load_json_config("./configs/main.json");
    transaction::Client tclient{cnf};

    // get transaction
    trans_filter filter{
            "1",
            10,
            std::string("2"),
            std::string("2001-09-10")
    };

    auto transactions = tclient.get(filter, {.data=user::privilege::SUPER});
    if (transactions.first == transaction::OK) {
        std::cout << "status - OK" << std::endl;
        for (const auto &t: transactions.second) {
            std::cout << "#################################\n";
            std::cout << t << std::endl;
        }
    } else {
        std::cout << "status - not OK: " << static_cast<std::underlying_type_t<transaction::status>>(transactions.first)
                  << std::endl;
    }

    // add transaction
    transaction_t tran{
            "0",
            "6390721926535760",
            "9573202978162608",
            "za pivo",
            10.0,
            transaction::CARD_TRANSFER
    };
    auto status = tclient.create(tran, {.data=user::privilege::SUPER});
    std::cout << "create status: " << static_cast<std::underlying_type_t<transaction::status>>(status) << std::endl;


    return 0;
}