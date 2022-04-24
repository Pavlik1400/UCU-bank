find_package(mongocxx CONFIG REQUIRED)
find_package(bsoncxx CONFIG REQUIRED)

set(SOURCES service.cpp utils.cpp)
set(HEADERS service.h utils.h)

add_executable(${ACCOUNT} account.cpp
        ${SOURCES} ${HEADERS}
)
target_link_libraries(${ACCOUNT} PRIVATE ${BASIC}
        ${USER}.client
        ${TOOLS}
        mongo::mongocxx_static
        mongo::bsoncxx_static
)

##########################################

set(CLI ${ACCOUNT}.cli)
add_executable(${CLI} account.cli.cpp)
target_link_libraries(${CLI} PRIVATE ${ACCOUNT}.client
        ${TOOLS}
)