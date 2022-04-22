find_package(Drogon CONFIG REQUIRED)
find_package(nlohmann_json CONFIG REQUIRED)
find_package(Boost REQUIRED log)
find_package(rpclib CONFIG REQUIRED)
find_package(serdepp CONFIG)
find_package(libpqxx CONFIG REQUIRED)

set(HEADERS
        account.hpp user.hpp transaction.hpp api_utils.hpp Filters.hpp
        ../basic/MessageSerializer.hpp
        ../service_tools/utils.hpp
        )
set(SOURCES
        account.cpp user.cpp transaction.cpp api_utils.cpp Filters.cpp
        ../basic/MessageSerializer.cpp
        ../service_tools/utils.cpp
        )

add_executable(${GATEWAY} main.cpp
        ../basic/MessageSerializer.cpp
        ../service_tools/utils.cpp

        ${ACCOUNT_SOURCES} ${ACCOUNT_HEADERS}
        ${USER_SOURCES} ${USER_HEADERS}
        ${TRANSACTION_SOURCES} ${TRANSACTION_HEADERS}
#        ${AUTH_SOURCES} ${AUTH_HEADERS}
        ../auth/constants.hpp ../auth/client.hpp ../auth/client.cpp

        ${TOOLS_SOURCES} ${TOOLS_HEADERS}

        ${SOURCES} ${HEADERS}
        )
target_include_directories(${GATEWAY} PRIVATE
        ${RPCLIB_INCLUDE_DIR}
        ${ROOT_INCLUDE_DIRECTORIES}
        )

target_link_libraries(${GATEWAY} PRIVATE
        rpclib::rpc
        serdepp::serdepp
        nlohmann_json::nlohmann_json
        Boost::boost Boost::log
        libpqxx::pqxx

        Drogon::Drogon
        )