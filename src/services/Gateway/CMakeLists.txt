find_package(Drogon CONFIG REQUIRED)
find_package(nlohmann_json CONFIG REQUIRED)
find_package(Boost REQUIRED log)
find_package(rpclib CONFIG REQUIRED)
find_package(serdepp CONFIG)


set(OTHER_SOURCES ../Account/src/AccountClient.cpp ../BasicMicroservice/src/MessageSerializer.cpp
        ../service_tools/utils.cpp
#        ../BasicMicroservice/src/logging.cpp
        )
set(OTHER_HEADERS ../Account/include/AccountClient.h ../Account/include/account_constants.h
        ../BasicMicroservice/include/MessageSerializer.hpp ../service_tools/utils.hpp
#        ../BasicMicroservice/include/logging.hpp
        )
set(SOURCES main.cpp UserAPI.cpp AccountAPI.cpp TransactionAPI.cpp Filters.cpp api_utils.cpp ${OTHER_SOURCES})
set(HEADERS UserAPI.hpp AccountAPI.hpp TransactionAPI.hpp Filters.hpp api_utils.hpp ${OTHER_HEADERS})
add_executable(${EXE_10} ${SOURCES} ${HEADERS})
target_include_directories(${EXE_10} PRIVATE include .. ../Account/include ../BasicMicroservice/include
        ${RPCLIB_INCLUDE_DIR})
target_link_libraries(${EXE_10} PRIVATE Drogon::Drogon rpclib::rpc serdepp::serdepp nlohmann_json::nlohmann_json
        Boost::boost Boost::log)