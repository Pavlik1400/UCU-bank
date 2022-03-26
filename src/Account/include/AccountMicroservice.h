#ifndef UCU_BANK_ACCOUNTMICROSERVICE_H
#define UCU_BANK_ACCOUNTMICROSERVICE_H

#include <mongocxx/instance.hpp>
#include <mongocxx/uri.hpp>
#include <mongocxx/client.hpp>
#include "BasicMicroservice.hpp"
namespace n = nlohmann;
class AccountMicroservice : BasicMicroservice {

private:
    mongocxx::instance instance{}; // This should be done only once.
    mongocxx::uri uri{"mongodb://localhost:27017/?replicaSet=rs0"};
    mongocxx::client client = mongocxx::client(uri);
    mongocxx::database db;

    // collections in DB
    mongocxx::collection users;
    mongocxx::write_concern wc_majority{};
    mongocxx::read_concern rc_local{};
    mongocxx::read_preference rp_primary{};
    mongocxx::options::transaction sopts;
    mongocxx::client_session session = client.start_session();
    std::map<int, void (AccountMicroservice::*)(const n::json &)> selector = {
            {0, &AccountMicroservice::create},
            {1, &AccountMicroservice::get},
            {2, &AccountMicroservice::update},
            {3, &AccountMicroservice::remove}
    };

public:
    void custom_start() override;
    void receive_callback(const nlohmann::json &msg) override;
    void create(const n::json &msg);
    void get(const n::json &msg);
    void update(const n::json &msg);
    void remove(const n::json &msg);



};


#endif //UCU_BANK_ACCOUNTMICROSERVICE_H
