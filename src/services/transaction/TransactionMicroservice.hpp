#ifndef UCU_BANK_TRANSACTIONMICROSERVICE_HPP
#define UCU_BANK_TRANSACTIONMICROSERVICE_HPP

#include "basic/BasicMicroservice.hpp"
#include "transaction_constants.hpp"
#include "account/AccountClient.h"
#include <ostream>
#include <pqxx/pqxx>

namespace pq = pqxx;
using add_transaction_res = std::pair<transaction::status, unsigned long long>;
using tran_query_res = std::pair<transaction::status, std::vector<Transaction>>;

class TransactionMicroservice: public BasicMicroservice {
public:
    TransactionMicroservice(const nlohmann::json &cnf);

    void start() override;

    void finish() override;

    virtual ~TransactionMicroservice();

public:
    transaction::status make_transaction(const Transaction &tran);
    tran_query_res get_transaction(const TransactionFilter &filter);

private:
    transaction::status verify_transaction(const Transaction &tran);
    add_transaction_res add_transaction_to_db(const Transaction &tran, transaction::db_entry_status status);
    transaction::status update_transaction_status(unsigned long long entry_id, transaction::db_entry_status status);
    transaction::status delete_transaction(unsigned long long entry_id);
    void register_methods();

private:
    AccountClient accountClient;
    std::optional<pq::connection> pq_connection;
    const nlohmann::json &cnf;
};


#endif //UCU_BANK_TRANSACTIONMICROSERVICE_HPP
