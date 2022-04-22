find_package(serdepp CONFIG)
find_package(rpclib CONFIG REQUIRED)
find_package(Boost REQUIRED log)
find_package(redis++ CONFIG REQUIRED)
find_package(libpqxx CONFIG REQUIRED)
find_package(nlohmann_json CONFIG REQUIRED)

set(SOURCES service.cpp)
set(HEADERS service.hpp)

add_executable(${TRANSACTION} main.cpp
        ${BASIC_SOURCES} ${BASIC_HEADERS}
        ${TOOLS_SOURCES} ${TOOLS_HEADERS}
        ${ACCOUNT_SOURCES} ${ACCOUNT_HEADERS}
        ${TRANSACTION_SOURCES} ${TRANSACTION_HEADERS}
        ${SOURCES} ${HEADERS}
        )


target_include_directories(${TRANSACTION} PRIVATE
        ${BASIC_INCLUDE_DIRECTORIES}
        ${ACCOUNT_INCLUDE_DIRECTORIES}
        ${ROOT_INCLUDE_DIRECTORIES}
        )

target_link_libraries(${TRANSACTION}
        ${BASIC_INCLUDE_DEP_LIBRARIES}
        libpqxx::pqxx
        )

add_executable(tran_test test.cpp ${TRANSACTION_SOURCES} ${TRANSACTION_HEADERS})
target_include_directories(tran_test PRIVATE
        ${BASIC_INCLUDE_DIRECTORIES}
        ${ROOT_INCLUDE_DIRECTORIES}
        )

target_link_libraries(tran_test
        ${BASIC_INCLUDE_DEP_LIBRARIES}
        libpqxx::pqxx
        )