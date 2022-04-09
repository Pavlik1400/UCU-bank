find_package(serdepp CONFIG)
find_package(rpclib CONFIG REQUIRED)
find_package(Boost REQUIRED log)
find_package(redis++ CONFIG REQUIRED)
find_package(libpqxx CONFIG REQUIRED)

set(BASIC_SOURCES ../BasicMicroservice/src/BasicMicroservice.cpp ../BasicMicroservice/src/MessageSerializer.cpp
        ../BasicMicroservice/src/logging.cpp)
set(BASIC_HEADERS ../BasicMicroservice/include/BasicMicroservice.hpp ../BasicMicroservice/include/constants.hpp
        ../BasicMicroservice/include/MessageSerializer.hpp ../BasicMicroservice/include/logging.hpp)
set(SOURCES src/main.cpp src/TransactionMicroservice.cpp ${BASIC_SOURCES})
set(HEADERS include/TransactionMicroservice.hpp include/status.hpp ${BASIC_HEADERS})
add_executable(${EXE_13} ${SOURCES} ${HEADERS})
target_include_directories(${EXE_13} PRIVATE ${RPCLIB_INCLUDE_DIR} ${HIREDIS_HEADER} ${REDIS_PLUS_PLUS_HEADER}
        include .. ../BasicMicroservice/include)
target_link_libraries(${EXE_13} libpqxx::pqxx Boost::boost Boost::log rpclib::rpc redis++::redis++_static)

