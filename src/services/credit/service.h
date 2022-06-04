#ifndef UCU_BANK_CREDIT_SERVICE_H
#define UCU_BANK_CREDIT_SERVICE_H

#include <chrono>
#include <thread>
#include <bsoncxx/json.hpp>
#include <mongocxx/client.hpp>
#include <mongocxx/stdx.hpp>
#include <mongocxx/uri.hpp>
#include <mongocxx/instance.hpp>
#include <mongocxx/exception/exception.hpp>
#include <bsoncxx/builder/stream/helpers.hpp>
#include <bsoncxx/builder/stream/document.hpp>
#include <bsoncxx/builder/stream/array.hpp>
#include <boost/date_time/gregorian/gregorian_types.hpp>
#include <boost/date_time/posix_time/posix_time_types.hpp>
#include <boost/bind/bind.hpp>
#include <boost/asio.hpp>
#include <boost/thread.hpp>
#include <boost/thread/thread_pool.hpp>

#include "basic/BasicMicroservice.hpp"
#include "transaction/client.hpp"
#include "user/client.h"
#include "account/client.h"
#include "credit/constants.h"
#include "auth/constants.hpp"
#include "user/constants.h"


using bsoncxx::builder::stream::close_array;
using bsoncxx::builder::stream::close_document;
using bsoncxx::builder::stream::document;
using bsoncxx::builder::stream::finalize;
using bsoncxx::builder::stream::open_array;
using bsoncxx::builder::stream::open_document;
using bsoncxx::builder::basic::kvp;
using bsoncxx::builder::basic::sub_array;

namespace gregorian = boost::gregorian;
namespace posix_time = boost::posix_time;
namespace asio = boost::asio;

namespace credit {
    class Service : public BasicMicroservice {

    private:
        const std::string SET = "$set";
        const std::string PUSH = "$push";
        const std::string PULL = "$pull";
        const std::string IN = "$in";
        const std::string INC = "$inc";
        const std::string OID = "$oid";

        mongocxx::instance instance{}; // This should be done only once.
        mongocxx::uri uri{"mongodb://localhost:27017/?replicaSet=rs0"};
        mongocxx::client client = mongocxx::client(uri);
        mongocxx::client client_for_thread = mongocxx::client(uri);
        mongocxx::database db;
        mongocxx::database db_for_thread;

        // collections in DB
        mongocxx::collection credits_collection;
        mongocxx::collection credits_collection_for_thread;
        mongocxx::write_concern wc_majority{};
        mongocxx::read_concern rc_local{};
        mongocxx::read_preference rp_primary{};
        mongocxx::options::transaction sopts;
        mongocxx::client_session session = client.start_session();
        mongocxx::client_session session_for_thread = client_for_thread.start_session();

        const nlohmann::json cnf;
        transaction::Client transactionClient;
        account::Client accountClient;
        user::Client userClient;

        user_t super_user;
        account_t super_user_acc;

        asio::io_service io_;
        asio::deadline_timer timer_;
        boost::thread_group worker_threads;

        std::string credit_update_measure;
        int credit_update_period;

    public:
        explicit Service(const nlohmann::json &cnf);

        void start() override;

        void finish() override;

        credit::status create(const std::string &user_id, const std::string &card, int credit_type, double balance, const auth::AuthDU &ctrl);

        std::pair<credit::status, std::vector<credit_t>> get_all(const std::string &user_id, const auth::AuthDU &ctrl);

        credit::status finish_credit(const std::string &user_id, const std::string &credit_id, const auth::AuthDU &ctrl);

    private:
        credit_t deserialize(const bsoncxx::document::view &info, const auth::AuthDU &ctrl);

        credit::status reduce_credit_amount(const credit_t &credit_inst, double amount, mongocxx::collection &coll, mongocxx::client_session &client_sess);

        void credit_scheduled_job();
    };
}



#endif //UCU_BANK_CREDIT_SERVICE_H
