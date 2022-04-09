find_package(serdepp CONFIG)
find_package(redis++ CONFIG REQUIRED)
find_package(rpclib CONFIG REQUIRED)
find_package(mongocxx CONFIG REQUIRED)
find_package(bsoncxx CONFIG REQUIRED)
find_package(Boost REQUIRED log)

set(EXTERNAL_SOURCES ../BasicMicroservice/src/BasicMicroservice.cpp ../BasicMicroservice/src/MessageSerializer.cpp
        ../BasicMicroservice/src/logging.cpp)
set(EXTERNAL_HEADERS ../BasicMicroservice/include/BasicMicroservice.hpp ../BasicMicroservice/include/constants.hpp
        ../BasicMicroservice/include/MessageSerializer.hpp ../BasicMicroservice/include/logging.hpp)

set(SOURCES start.cpp src/AccountMicroservice.cpp src/AccountClient.cpp src/utils.cpp)
set(HEADERS include/AccountMicroservice.h include/AccountClient.h include/account_constants.h include/utils.h)
add_executable(${EXE_08} ${SOURCES} ${HEADERS} ${EXTERNAL_SOURCES} ${EXTERNAL_HEADERS})
target_include_directories(${EXE_08} PRIVATE include ../BasicMicroservice/include)
target_link_libraries(${EXE_08} mongo::mongocxx_static
                                mongo::bsoncxx_static
                                serdepp::serdepp
                                redis++::redis++_static
                                rpclib::rpc
                                Boost::boost
                                Boost::log)
set(CLIENT account_client)
add_executable(${CLIENT} client.cpp src/AccountClient.cpp include/AccountClient.h include/account_constants.h)
target_include_directories(${CLIENT} PRIVATE include)
target_link_libraries(${CLIENT} mongo::mongocxx_static
        mongo::bsoncxx_static
        serdepp::serdepp
        redis++::redis++_static
        rpclib::rpc
        Boost::boost
        Boost::log)


