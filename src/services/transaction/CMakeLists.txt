find_package(serdepp CONFIG)
find_package(rpclib CONFIG REQUIRED)
find_package(Boost REQUIRED log)
find_package(redis++ CONFIG REQUIRED)
find_package(libpqxx CONFIG REQUIRED)

set(BASIC_SOURCES
        ../basic/BasicMicroservice.cpp
        ../basic/MessageSerializer.cpp
        ../basic/logging.cpp
        )
set(BASIC_HEADERS
        ../basic/BasicMicroservice.hpp
        ../basic/constants.hpp
        ../basic/MessageSerializer.hpp
        ../basic/logging.hpp
        )
set(SOURCES
        ${BASIC_SOURCES}
        service.cpp
        constants.cpp
        client.cpp

        ../service_tools/utils.cpp
        ../account/AccountClient.cpp
        )
set(HEADERS
        ${BASIC_HEADERS}
        service.hpp
        constants.hpp
        client.hpp

        ../service_tools/utils.hpp

        ../account/AccountClient.h
        )

add_executable(${EXE_13} main.cpp ${SOURCES} ${HEADERS})

target_include_directories(${EXE_13} PRIVATE
        ${RPCLIB_INCLUDE_DIR}
        ${HIREDIS_HEADER}
        ${REDIS_PLUS_PLUS_HEADER}
        ..
        )

target_link_libraries(${EXE_13} libpqxx::pqxx Boost::boost Boost::log rpclib::rpc redis++::redis++_static)

add_executable(tran_test test.cpp ${SOURCES} ${HEADERS})
target_include_directories(tran_test PRIVATE
        ${RPCLIB_INCLUDE_DIR}
        ${HIREDIS_HEADER}
        ${REDIS_PLUS_PLUS_HEADER}
        ..
        )
target_link_libraries(tran_test libpqxx::pqxx Boost::boost Boost::log rpclib::rpc redis++::redis++_static)

