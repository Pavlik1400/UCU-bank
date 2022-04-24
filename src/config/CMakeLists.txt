get_filename_component(ROOT_ "${CMAKE_CURRENT_SOURCE_DIR}/../services/" ABSOLUTE)
set(ROOT_INCLUDE_DIRECTORIES "${ROOT_}")

#=========================================#
# --------- BASIC MICROSERVICE ---------- #
#=========================================#
set(BASIC_ROOT "${ROOT_}/basic")

find_package(serdepp CONFIG)
find_package(nlohmann_json CONFIG REQUIRED)
find_package(redis++ CONFIG REQUIRED)
find_package(rpclib CONFIG REQUIRED)
find_package(Boost COMPONENTS log REQUIRED)

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

target_include_directories(${BASIC} PUBLIC ${ROOT_}
    ${RPCLIB_INCLUDE_DIR}
    ${HIREDIS_HEADER}
    ${REDIS_PLUS_PLUS_HEADER}
)

target_sources(${BASIC} INTERFACE ${BASIC_ROOT}/BasicMicroservice.hpp
    ${BASIC_ROOT}/logging.hpp
    ${BASIC_ROOT}/constants.hpp
    ${BASIC_ROOT}/MessageSerializer.hpp
)

#=========================================#
# --------- AUTH MICROSERVICE ----------- #
#=========================================#
set(AUTH_ROOT "${ROOT_}/auth")

add_library(${AUTH}.client SHARED ${AUTH_ROOT}/client.cpp)

target_link_libraries(${AUTH}.client rpclib::rpc)

target_include_directories(${AUTH}.client PUBLIC "${ROOT_}"
    ${RPCLIB_INCLUDE_DIR}
)

target_sources(${AUTH}.client INTERFACE ${AUTH_ROOT}/client.hpp
    ${AUTH_ROOT}/constants.hpp
)

#=========================================#
# --------- ACCOUNT MICROSERVICE -------- #
#=========================================#
set(ACCOUNT_ROOT "${ROOT_}/account")
add_library(${ACCOUNT}.client SHARED ${ACCOUNT_ROOT}/client.cpp
    ${ACCOUNT_ROOT}/client.cpp
)

target_link_libraries(${ACCOUNT}.client rpclib::rpc)

target_include_directories(${ACCOUNT}.client PUBLIC "${ROOT_}"
    ${RPCLIB_INCLUDE_DIR}
)

target_sources(${ACCOUNT}.client INTERFACE ${ACCOUNT_ROOT}/client.h
    ${ACCOUNT_ROOT}/constants.h
)

#=========================================#
# --------- USER MICROSERVICE ----------- #
#=========================================#
set(USER_ROOT "${ROOT_}/user")
add_library(${USER}.client SHARED ${USER_ROOT}/client.cpp)

target_link_libraries(${USER}.client rpclib::rpc)

target_include_directories(${USER}.client PUBLIC "${ROOT_}"
    ${RPCLIB_INCLUDE_DIR}
)

target_sources(${USER}.client INTERFACE ${USER_ROOT}/client.h
    ${USER_ROOT}/constants.h
)

#=========================================#
# ---------- TRANSACTION ---------------- #
#=========================================#
set(TRANSACTION_ROOT "${ROOT_}/transaction")
add_library(${TRANSACTION}.client SHARED ${TRANSACTION_ROOT}/client.cpp
    ${TRANSACTION_ROOT}/constants.cpp
)

target_link_libraries(${TRANSACTION}.client rpclib::rpc)

target_include_directories(${TRANSACTION}.client PUBLIC "${ROOT_}"
    ${RPCLIB_INCLUDE_DIR}
)

target_sources(${TRANSACTION}.client INTERFACE ${TRANSACTION_ROOT}/client.hpp
    ${TRANSACTION_ROOT}/constants.hpp
)

#=========================================#
# --------- SERVICE TOOLS --------------- #
#=========================================#
set(TOOLS_ROOT "${ROOT_}/service_tools")
add_library(${TOOLS} SHARED ${TOOLS_ROOT}/utils.cpp)

target_link_libraries(${TOOLS} basic rpclib::rpc
    serdepp::serdepp
    nlohmann_json::nlohmann_json
)

target_include_directories(${TOOLS} PUBLIC "${ROOT_}"
    ${RPCLIB_INCLUDE_DIR}
)

target_sources(${TOOLS} INTERFACE ${TOOLS_ROOT}/utils.hpp)