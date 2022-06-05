#include "api_base.hpp"


namespace ucubank_api::v2 {
    APIBase::APIBase(const nlohmann::json &cnf) :
            auth_client(cnf) {
    }

}
