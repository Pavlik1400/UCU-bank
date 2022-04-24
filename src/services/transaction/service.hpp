#ifndef UCU_BANK_TRANSACTION_SERVICE_HPP
#define UCU_BANK_TRANSACTION_SERVICE_HPP

#include "basic/BasicMicroservice.hpp"
#include "constants.hpp"
#include "account/client.h"
#include <ostream>
#include <pqxx/pqxx>

namespace pq = pqxx;

namespace transaction {
    class Service : public BasicMicroservice {
    public:
        explicit Service(const nlohmann::json &cnf);

        void start() override;

        void finish() override;

        ~Service() override;

    public:
        transaction::status make_transaction(const transaction_t &tran);

        tran_query_res get_transaction(const trans_filter &filter);

    private:
        transaction::status verify_transaction(const transaction_t &tran);

        add_transaction_res add_transaction_to_db(const transaction_t &tran, transaction::db_entry_status status);

        transaction::status update_transaction_status(unsigned long long entry_id, transaction::db_entry_status status);

        transaction::status delete_transaction(unsigned long long entry_id);

        void register_methods();

    private:
        account::Client accountClient;
        std::optional<pq::connection> pq_connection;
        const nlohmann::json &cnf;
    };
}

#endif //UCU_BANK_TRANSACTION_SERVICE_HPP
