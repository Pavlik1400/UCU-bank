#ifndef UCU_BANK_SERVICE_HPP
#define UCU_BANK_SERVICE_HPP

#include "basic/BasicMicroservice.hpp"
#include "constants.hpp"
#include "account/AccountClient.h"
#include <ostream>
#include <pqxx/pqxx>

namespace pq = pqxx;

namespace transaction {
    class Service : public BasicMicroservice {
    public:
        Service(const nlohmann::json &cnf);

        void start() override;

        void finish() override;

        virtual ~Service();

    public:
        transaction::status make_transaction(const Transfer &tran);

        tran_query_res get_transaction(const TransactionFilter &filter);

    private:
        transaction::status verify_transaction(const Transfer &tran);

        add_transaction_res add_transaction_to_db(const Transfer &tran, transaction::db_entry_status status);

        transaction::status update_transaction_status(unsigned long long entry_id, transaction::db_entry_status status);

        transaction::status delete_transaction(unsigned long long entry_id);

        void register_methods();

    private:
        AccountClient accountClient;
        std::optional<pq::connection> pq_connection;
        const nlohmann::json &cnf;
    };
}

#endif //UCU_BANK_SERVICE_HPP
