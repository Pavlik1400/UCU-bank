find_package(serdepp CONFIG)
find_package(nlohmann_json CONFIG REQUIRED)
find_package(redis++ CONFIG REQUIRED)
find_package(rpclib CONFIG REQUIRED)
find_package(Boost REQUIRED log)


add_executable(${BASIC}
        main.cpp

        BasicMicroservice.cpp
        BasicMicroservice.hpp

        MessageSerializer.cpp
        MessageSerializer.hpp

        constants.hpp

        logging.cpp
        logging.hpp
        )

target_include_directories(${BASIC} PRIVATE ${RPCLIB_INCLUDE_DIR} ${HIREDIS_HEADER} ${REDIS_PLUS_PLUS_HEADER} ..)
target_link_libraries(${BASIC} PRIVATE rpclib::rpc serdepp::serdepp nlohmann_json::nlohmann_json
        redis++::redis++_static Boost::boost Boost::log)
