get_filename_component(ROOT_ "${CMAKE_CURRENT_SOURCE_DIR}/../services/" ABSOLUTE)
set(ROOT_INCLUDE_DIRECTORIES "${ROOT_}" PARENT_SCOPE)

#=========================================#
# --------- BASIC MICROSERVICE ---------- #
#=========================================#
set(BASIC_ROOT "${ROOT_}/basic")
set(BASIC_INCLUDE_DIRECTORIES "${BASIC_ROOT}/include"
    PARENT_SCOPE
)
set(BASIC_SOURCES ${BASIC_ROOT}/BasicMicroservice.cpp
    ${BASIC_ROOT}/logging.cpp
    ${BASIC_ROOT}/MessageSerializer.cpp
    PARENT_SCOPE
)
set(BASIC_HEADERS ${BASIC_ROOT}/BasicMicroservice.hpp
    # INNER
    ${BASIC_ROOT}/logging.hpp
    ${BASIC_ROOT}/constants.hpp
    ${BASIC_ROOT}/MessageSerializer.hpp

    # EXTERNAL
    ${RPCLIB_INCLUDE_DIR}
    ${HIREDIS_HEADER}
    ${REDIS_PLUS_PLUS_HEADER}
    PARENT_SCOPE
)
set(BASIC_INCLUDE_DEP_LIBRARIES rpclib::rpc
    serdepp::serdepp
    nlohmann_json::nlohmann_json
    redis++::redis++_static
    Boost::boost
    Boost::log
    PARENT_SCOPE
)

#=========================================#
# --------- AUTH MICROSERVICE ----------- #
#=========================================#
set(AUTH_ROOT "${ROOT_}/auth")
set(AUTH_INCLUDE_DIRECTORIES "${AUTH_ROOT}"
    PARENT_SCOPE
)
set(AUTH_SOURCES ${AUTH_ROOT}/service.cpp
    PARENT_SCOPE
)
set(AUTH_HEADERS ${AUTH_ROOT}/service.hpp
    ${AUTH_ROOT}/constants.hpp
    PARENT_SCOPE
)

#=========================================#
# --------- ACCOUNT MICROSERVICE -------- #
#=========================================#
set(ACCOUNT_ROOT "${ROOT_}/account")
set(ACCOUNT_INCLUDE_DIRECTORIES "${ACCOUNT_ROOT}"
    PARENT_SCOPE
)
set(ACCOUNT_SOURCES
    ${ACCOUNT_ROOT}/client.cpp
    ${ACCOUNT_ROOT}/utils.cpp
    PARENT_SCOPE
)
set(ACCOUNT_HEADERS
    ${ACCOUNT_ROOT}/client.h
    ${ACCOUNT_ROOT}/constants.h
    PARENT_SCOPE
)
set(ACCOUNT_INCLUDE_DEP_LIBRARIES
    mongo::mongocxx_static
    mongo::bsoncxx_static
    PARENT_SCOPE
)

#=========================================#
# --------- USER MICROSERVICE ----------- #
#=========================================#
set(USER_ROOT "${ROOT_}/user")
set(USER_INCLUDE_DIRECTORIES "${USER_ROOT}"
    PARENT_SCOPE
)
set(USER_SOURCES
    ${USER_ROOT}/client.cpp
    PARENT_SCOPE
)
set(USER_HEADERS
    ${USER_ROOT}/client.h
    ${USER_ROOT}/constants.h
    PARENT_SCOPE
)
set(USER_INCLUDE_DEP_LIBRARIES
    mongo::mongocxx_static
    mongo::bsoncxx_static
    PARENT_SCOPE
)

#=========================================#
# --------- SERVICE TOOLS --------------- #
#=========================================#
set(TOOLS_ROOT "${ROOT_}/service_tools")
set(TOOLS_INCLUDE_DIRECTORIES ${TOOLS_ROOT}
    PARENT_SCOPE
)
set(TOOLS_SOURCES #${ACCOUNT_ROOT}/src/AccountMicroservice.cpp
    ${TOOLS_ROOT}/utils.cpp
   # ${USER_ROOT}/src/utils.cpp
    PARENT_SCOPE
)
set(TOOLS_HEADERS #${ACCOUNT_ROOT}/include/AccountMicroservice.h
    ${TOOLS_ROOT}/utils.hpp
    PARENT_SCOPE
)

#=========================================#
# ---------- TRANSACTION ---------------- #
#=========================================#
set(TRANSACTION_ROOT "${ROOT_}/transaction")
set(TRANSACTION_INCLUDE_DIRECTORIES "${TRANSACTION_ROOT}" PARENT_SCOPE)

set(TRANSACTION_HEADERS
        ${TRANSACTION_ROOT}/client.hpp
        ${TRANSACTION_ROOT}/constants.hpp
        PARENT_SCOPE
        )

set(TRANSACTION_SOURCES
        ${TRANSACTION_ROOT}/client.cpp
        ${TRANSACTION_ROOT}/constants.cpp
        PARENT_SCOPE
        )

set(TRANSACTION_INCLUDE_DEP_LIBRARIES
        PARENT_SCOPE
        )