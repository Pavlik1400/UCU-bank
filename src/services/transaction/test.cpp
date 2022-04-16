#include "transaction/client.hpp"
#include "service_tools/utils.hpp"
#include <iostream>


int main() {
    auto cnf = load_json_config("./configs/main.json");
    transaction::Client tclient{cnf};

    // get transaction
    TransactionFilter filter{
            "1",
            10,
            std::string("2"),
            std::string("2001-09-10")
    };

    auto transactions = tclient.get(filter);
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
    Transaction tran{
            "0",
            "6390721926535760",
            "9822957320297810",
            "za pivo",
            10.0,
            transaction::CARD_TRANSFER
    };
    auto status = tclient.create(tran);
    std::cout << "create status: " << static_cast<std::underlying_type_t<transaction::status>>(status) << std::endl;


    return 0;
}