find_package(serdepp CONFIG)
find_package(redis++ CONFIG REQUIRED)
find_package(rpclib CONFIG REQUIRED)
find_package(mongocxx CONFIG REQUIRED)
find_package(bsoncxx CONFIG REQUIRED)
find_package(Boost REQUIRED log)

set(EXTERNAL_SOURCES
        ../basic/BasicMicroservice.cpp
        ../basic/MessageSerializer.cpp
        ../basic/logging.cpp
        AccountClient.cpp
        )
set(EXTERNAL_HEADERS
        ../basic/BasicMicroservice.hpp
        ../basic/constants.hpp
        ../basic/MessageSerializer.hpp
        ../basic/logging.hpp
        AccountClient.h
        )

set(SOURCES start.cpp AccountMicroservice.cpp AccountClient.cpp utils.cpp)
set(HEADERS AccountMicroservice.h AccountClient.h account_constants.h utils.h)

add_executable(${EXE_08} ${SOURCES} ${HEADERS} ${EXTERNAL_SOURCES} ${EXTERNAL_HEADERS})

target_include_directories(${EXE_08} PRIVATE
        ..
        )

target_link_libraries(${EXE_08} mongo::mongocxx_static
        mongo::bsoncxx_static
        serdepp::serdepp
        redis++::redis++_static
        rpclib::rpc
        Boost::boost
        Boost::log)

set(CLIENT account_client)
add_executable(${CLIENT} client.cpp AccountClient.cpp AccountClient.h account_constants.h)
target_include_directories(${CLIENT} PRIVATE .. )
target_link_libraries(${CLIENT} mongo::mongocxx_static
        mongo::bsoncxx_static
        serdepp::serdepp
        redis++::redis++_static
        rpclib::rpc
        Boost::boost
        Boost::log
        )


