#include "TransactionClient.hpp"
#include "service_tools/utils.hpp"
#include <iostream>

int main() {
    auto cnf = load_json_config("./configs/main.json");
    TransactionClient tclient{cnf};

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
        for (const auto& t: transactions.second) {
            std::cout << "#################################\n";
            std::cout << t << std::endl;
        }
    } else {
        std::cout << "status - not OK: " << transactions.first << std::endl;
    }

    // add transaction
//    Transaction tran{"123", };
    return 0;
}