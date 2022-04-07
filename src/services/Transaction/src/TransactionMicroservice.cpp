#include "../include/TransactionMicroservice.hpp"
#include "Account/include/account_constants.h"
#include "Account/include/Account.h"

TransactionMicroservice::TransactionMicroservice(const RpcServerAddress &account_adr, const RpcServerAddress &auth_addr,
                                                 uint16_t port, const std::string &redis_url) :
        BasicMicroservice(port, redis_url),
        account_rpc(account_adr.address, account_adr.port),
        auth_rpc(auth_addr.address, auth_addr.port) {
    CUSTOM_LOG(lg, debug) << "Transaction service initialized";
}

void TransactionMicroservice::custom_start() {
    CUSTOM_LOG(lg, info) << "Transaction service started";
}

void TransactionMicroservice::custom_finish() {
    CUSTOM_LOG(lg, info) << "Transcation service finished";
}

TransactionStatus
TransactionMicroservice::make_transaction(const Transaction &tran) {
    // TODO: check if user is loggined - Auth serice
//    if (!auth_rpc.is_logined(tran.user_id)) {
//        return TransactionStatus::IS_NOT_LOGINED;
//    }
    // TODO: check if user has access to this card - Account service
//    get_resp = account_rpc.get(tran.from_acc_id);
//    if (get_resp.status != response::type::OK) {
//        switch (get_resp.status) {
//            case response::type::NO_EXISTS:
//                return TransactionStatus::ACCOUNT_DOESNT_EXISTS;
//            default:
//                return TransactionStatus::FAILED;
//        }
//    }
//    Account acc_info = get_resp.account;
//    if (acc_info.user_id != tran.user_id) {
//        return TransactionStatus::TRANSACTION_FORBIDEN;
//    }
    // TODO: check if there is enough money on the card - Account service
//    if (acc_info.amount < tran.amount) {
//        return TransactionStatus::NOT_ENOUGH_MONEY;
//    }


    return TransactionStatus::OK;
}

TransactionMicroservice::~TransactionMicroservice() = default;

