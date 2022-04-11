find_package(serdepp CONFIG)
find_package(rpclib CONFIG REQUIRED)
find_package(Boost REQUIRED log)
find_package(redis++ CONFIG REQUIRED)
find_package(libpqxx CONFIG REQUIRED)

set(BASIC_SOURCES ../BasicMicroservice/src/BasicMicroservice.cpp ../BasicMicroservice/src/MessageSerializer.cpp
        ../BasicMicroservice/src/logging.cpp)
set(BASIC_HEADERS ../BasicMicroservice/include/BasicMicroservice.hpp ../BasicMicroservice/include/constants.hpp
        ../BasicMicroservice/include/MessageSerializer.hpp ../BasicMicroservice/include/logging.hpp)
set(SOURCES ${BASIC_SOURCES} TransactionMicroservice.cpp transaction_constants.cpp TransactionClient.cpp
        ../service_tools/utils.hpp ../service_tools/utils.cpp ../Account/src/AccountClient.cpp)
set(HEADERS  ${BASIC_HEADERS} TransactionMicroservice.hpp transaction_constants.hpp TransactionClient.hpp
        ../Account/include/AccountClient.h)
add_executable(${EXE_13} main.cpp ${SOURCES} ${HEADERS})
target_include_directories(${EXE_13} PRIVATE ${RPCLIB_INCLUDE_DIR} ${HIREDIS_HEADER} ${REDIS_PLUS_PLUS_HEADER}
        include .. ../BasicMicroservice/include ../Account/include)
target_link_libraries(${EXE_13} libpqxx::pqxx Boost::boost Boost::log rpclib::rpc redis++::redis++_static)

add_executable(tran_test test.cpp ${SOURCES} ${HEADERS})
target_include_directories(tran_test PRIVATE ${RPCLIB_INCLUDE_DIR} ${HIREDIS_HEADER} ${REDIS_PLUS_PLUS_HEADER}
        include .. ../BasicMicroservice/include ../Account/include)
target_link_libraries(tran_test libpqxx::pqxx Boost::boost Boost::log rpclib::rpc redis++::redis++_static)

