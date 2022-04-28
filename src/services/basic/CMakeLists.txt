find_package(serdepp CONFIG REQUIRED)
find_package(nlohmann_json CONFIG REQUIRED)
find_package(rpclib CONFIG REQUIRED)
find_package(Boost COMPONENTS log REQUIRED)
find_package(redis++ CONFIG REQUIRED)

set(BASIC_ROOT "${ROOT_INCLUDE_DIRECTORIES}/basic")
find_package(redis++ CONFIG)

add_library(${BASIC} SHARED ${BASIC_ROOT}/BasicMicroservice.cpp
    ${BASIC_ROOT}/logging.cpp
    ${BASIC_ROOT}/MessageSerializer.cpp
)

target_link_libraries(${BASIC} rpclib::rpc
    serdepp::serdepp
    nlohmann_json::nlohmann_json
    redis++::redis++_static
    Boost::boost
    Boost::log
)

target_include_directories(${BASIC} PUBLIC ${ROOT_INCLUDE_DIRECTORIES}
    ${RPCLIB_INCLUDE_DIR}
    ${HIREDIS_HEADER}
    ${REDIS_PLUS_PLUS_HEADER}
)

target_sources(${BASIC} INTERFACE ${BASIC_ROOT}/BasicMicroservice.hpp
    ${BASIC_ROOT}/logging.hpp
    ${BASIC_ROOT}/constants.hpp
    ${BASIC_ROOT}/MessageSerializer.hpp
)