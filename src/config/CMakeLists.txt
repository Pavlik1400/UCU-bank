get_filename_component(ROOT_ "${CMAKE_CURRENT_SOURCE_DIR}/../services/" ABSOLUTE)
set(ROOT_INCLUDE_DIRECTORIES "${ROOT_}" PARENT_SCOPE)

find_package(serdepp CONFIG)
find_package(nlohmann_json CONFIG)
find_package(rpclib CONFIG)

#=========================================#
# --------- AUTH MICROSERVICE ----------- #
#=========================================#
set(AUTH_ROOT "${ROOT_}/auth")

add_library(${AUTH}.client SHARED ${AUTH_ROOT}/client.cpp "${ROOT_}/client/client.hpp")

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
add_library(${ACCOUNT}.client SHARED ${ACCOUNT_ROOT}/client.cpp "${ROOT_}/client/client.hpp"
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
add_library(${USER}.client SHARED ${USER_ROOT}/client.cpp "${ROOT_}/client/client.hpp")

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
add_library(${TRANSACTION}.client SHARED ${TRANSACTION_ROOT}/client.cpp "${ROOT_}/client/client.hpp"
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

target_link_libraries(${TOOLS} rpclib::rpc
    serdepp::serdepp
    nlohmann_json::nlohmann_json
)

target_include_directories(${TOOLS} PUBLIC "${ROOT_}"
    ${RPCLIB_INCLUDE_DIR}
)

target_sources(${TOOLS} INTERFACE ${TOOLS_ROOT}/utils.hpp)