find_package(Drogon CONFIG REQUIRED)
find_package(nlohmann_json CONFIG REQUIRED)
find_package(Boost REQUIRED log)
find_package(rpclib CONFIG REQUIRED)
find_package(serdepp CONFIG)


set(OTHER_SOURCES
        ../basic/MessageSerializer.cpp
        ../service_tools/utils.cpp
        ../account/AccountClient.cpp
        ../user/client.cpp
        #        ../BasicMicroservice/src/logging.cpp
        )
set(OTHER_HEADERS
        ../basic/MessageSerializer.hpp
        ../service_tools/utils.hpp
        ../account/AccountClient.h
        ../account/account_constants.h
        ../user/client.h
        ../user/constants.h
        #        ../BasicMicroservice/include/logging.hpp
        )
set(SOURCES
        main.cpp
        user.cpp
        account.cpp
        Filters.cpp
        api_utils.cpp
        ${OTHER_SOURCES}
        )
set(HEADERS
        user.hpp
        account.hpp
        Filters.hpp
        api_utils.hpp
        ${OTHER_HEADERS}
        )
add_executable(${EXE_10} ${SOURCES} ${HEADERS})
target_include_directories(${EXE_10} PRIVATE .. ${RPCLIB_INCLUDE_DIR})
target_link_libraries(${EXE_10} PRIVATE
        Drogon::Drogon
        rpclib::rpc
        serdepp::serdepp
        nlohmann_json::nlohmann_json
        Boost::boost Boost::log
        )