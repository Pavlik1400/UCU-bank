find_package(serdepp CONFIG)
find_package(nlohmann_json CONFIG REQUIRED)
find_package(redis++ CONFIG REQUIRED)
find_package(rpclib CONFIG REQUIRED)
find_package(Boost REQUIRED log)


add_executable(${EXE_07} include/logging.hpp include/BasicMicroservice.hpp include/MessageSerializer.hpp
        include/constants.hpp src/BasicMicroservice.cpp src/MessageSerializer.cpp src/main.cpp)

target_include_directories(${EXE_07} PRIVATE ${RPCLIB_INCLUDE_DIR} ${HIREDIS_HEADER} ${REDIS_PLUS_PLUS_HEADER} include)
target_link_libraries(${EXE_07} PRIVATE rpclib::rpc serdepp::serdepp nlohmann_json::nlohmann_json
        redis++::redis++_static Boost::boost Boost::log)
