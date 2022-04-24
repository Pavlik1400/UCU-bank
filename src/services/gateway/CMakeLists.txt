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
        ${SOURCES} ${HEADERS}
)
target_include_directories(${GATEWAY} PRIVATE
        ${RPCLIB_INCLUDE_DIR}
)
target_link_libraries(${GATEWAY} PRIVATE
        ${ACCOUNT}.client 
        ${USER}.client 
        ${TRANSACTION}.client 
        ${AUTH}.client
        ${TOOLS}
        rpclib::rpc
        serdepp::serdepp
        nlohmann_json::nlohmann_json
        Boost::boost Boost::log
        libpqxx::pqxx
        Drogon::Drogon
)