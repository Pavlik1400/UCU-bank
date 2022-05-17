find_package(libpqxx CONFIG REQUIRED)

set(SOURCES service.cpp constants.cpp)
set(HEADERS service.hpp constants.hpp)

add_executable(${TRANSACTION} main.cpp
        ${SOURCES} ${HEADERS}
)
target_link_libraries(${TRANSACTION} ${BASIC} 
        ${ACCOUNT}.client
        ${NOTIFICATION}.client
        ${TOOLS}
        libpqxx::pqxx
)

add_executable(tran_test test.cpp)
target_link_libraries(tran_test ${TRANSACTION}.client
        ${TOOLS}
        libpqxx::pqxx
)