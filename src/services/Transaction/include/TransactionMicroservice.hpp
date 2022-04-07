#ifndef UCU_BANK_TRANSACTIONMICROSERVICE_HPP
#define UCU_BANK_TRANSACTIONMICROSERVICE_HPP

#include "BasicMicroservice.hpp"
#include "status.hpp"

struct Transaction {
    const std::string &user_id;
    const std::string &from_acc_id;
    const std::string &to_acc_id;
    const std::string &description;
    const double amount;
};

class TransactionMicroservice: public BasicMicroservice {
    TransactionMicroservice(const RpcServerAddress &account_adr, const RpcServerAddress &auth_addr,
                            uint16_t port, const std::string &redis_url);

    void custom_start() override;

    void custom_finish() override;

    virtual ~TransactionMicroservice();

public:
    TransactionStatus make_transaction(const Transaction &tran);

private:
    rpc::client account_rpc;
    rpc::client auth_rpc;
};


#endif //UCU_BANK_TRANSACTIONMICROSERVICE_HPP
