find_package(serdepp CONFIG)
find_package(nlohmann_json CONFIG)
find_package(Boost REQUIRED)
find_package(redis++ CONFIG REQUIRED)
find_package(rpclib CONFIG REQUIRED)
find_package(mongocxx CONFIG REQUIRED)
find_package(bsoncxx CONFIG REQUIRED)
set(SOURCES src/Account.cpp src/AccountMicroservice.cpp ../BasicMicroservice/src/BasicMicroservice.cpp ../BasicMicroservice/src/MessageSerializer.cpp src/utils.cpp)
set(HEADERS include/Account.h include/AccountMicroservice.h ../BasicMicroservice/include/BasicMicroservice.hpp ../BasicMicroservice/include/constants.hpp include/constants.h include/utils.h)
add_executable(${EXE_08} ${SOURCES} ${HEADERS})
target_include_directories(${EXE_08} PRIVATE ${LIBMONGOCXX_INCLUDE_DIR})
target_include_directories(${EXE_08} PRIVATE ${LIBBSONCXX_INCLUDE_DIR})
target_include_directories(${EXE_08} PRIVATE ${Boost_INCLUDE_DIR} include ../BasicMicroservice/include)
target_link_libraries(${EXE_08} mongo::mongocxx_static mongo::bsoncxx_static serdepp::serdepp
        nlohmann_json::nlohmann_json redis++::redis++_static rpclib::rpc)


