find_package(mongocxx CONFIG REQUIRED)
find_package(bsoncxx CONFIG REQUIRED)
find_package(libpqxx CONFIG REQUIRED)

set(SOURCES service.cpp ../account/utils.cpp)
set(HEADERS service.h constants.h)

add_executable(${CREDIT} credit.cpp
        ${SOURCES} ${HEADERS}
)
target_link_libraries(${CREDIT} PRIVATE ${BASIC}
        ${TOOLS}
        ${USER}.client
        ${ACCOUNT}.client
        ${TRANSACTION}.client
        mongo::mongocxx_static
        mongo::bsoncxx_static
        libpqxx::pqxx
)

##########################################

set(CLI ${CREDIT}.cli)
add_executable(${CLI} ${CREDIT}.cli.cpp)
target_link_libraries(${CLI} PRIVATE
        ${ACCOUNT}.client
        ${CREDIT}.client
        ${TOOLS}
)