find_package(Drogon CONFIG REQUIRED)
find_package(nlohmann_json CONFIG REQUIRED)
find_package(Boost REQUIRED log)
find_package(rpclib CONFIG REQUIRED)
find_package(serdepp CONFIG)
find_package(libpqxx CONFIG REQUIRED)

set(API_V1_ROUTE "./ucubank_api/v1")
set(API_V2_ROUTE "./ucubank_api/v2")


set(HEADERS
        ${API_V1_ROUTE}/user/user.hpp
        ${API_V1_ROUTE}/account/account.hpp
        ${API_V1_ROUTE}/transaction/transaction.hpp
        ${API_V2_ROUTE}/user/user.hpp
        ${API_V2_ROUTE}/account/account.hpp
        ${API_V2_ROUTE}/transaction/transaction.hpp
        ${API_V2_ROUTE}/transaction_stats/transaction_stats.hpp
        ${API_V2_ROUTE}/credit/credit.hpp

        ucubank_api/api_utils.hpp
        ../basic/MessageSerializer.hpp
        ../service_tools/utils.hpp

        ucubank_api/v2/api_base.hpp
        ucubank_api/helpers.hpp
        )
set(SOURCES
        ${API_V1_ROUTE}/user/user.cpp
        ${API_V1_ROUTE}/account/account.cpp
        ${API_V1_ROUTE}/transaction/transaction.cpp
        ${API_V2_ROUTE}/user/user.cpp
        ${API_V2_ROUTE}/account/account.cpp
        ${API_V2_ROUTE}/transaction/transaction.cpp
        ${API_V2_ROUTE}/transaction_stats/transaction_stats.cpp
        ${API_V2_ROUTE}/credit/credit.cpp

        ucubank_api/api_utils.cpp
        ../basic/MessageSerializer.cpp
        ../service_tools/utils.cpp

        ucubank_api/v2/api_base.cpp
        )

add_executable(${GATEWAY} main.cpp ${SOURCES} ${HEADERS}
)
target_include_directories(${GATEWAY} PRIVATE ${RPCLIB_INCLUDE_DIR} .
)
target_link_libraries(${GATEWAY} PRIVATE
        ${ACCOUNT}.client 
        ${USER}.client 
        ${TRANSACTION}.client 
        ${AUTH}.client
        ${CREDIT}.client
        ${TOOLS}
        rpclib::rpc
        serdepp::serdepp
        nlohmann_json::nlohmann_json
        Boost::boost Boost::log
        libpqxx::pqxx
        Drogon::Drogon
)