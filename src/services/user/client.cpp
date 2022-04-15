#include "client.h"

namespace user {
    status Client::create(const user_t &user) {
        return client.call("create", user).as<status>();
    }

    std::pair<status, user_t> Client::get(const std::string &name, const std::string &phoneNo) {
        return client.call("get", name, phoneNo).as<std::pair<status, user_t>>();
    }

    status Client::remove(const std::string &name, const std::string &phoneNo) {
        return client.call("remove", name, phoneNo).as<status>();
    }

    status Client::exists(const std::string &name, const std::string &phoneNo) {
        return client.call("exists", name, phoneNo).as<status>();
    }

    status Client::valid_id(const std::string &id) {
        return client.call("valid_id", id).as<status>();
    }
}

//>>>>>>> 65419ab6e98365831fff73adcf38839526e3f16f
