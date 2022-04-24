find_package(mongocxx CONFIG REQUIRED)
find_package(bsoncxx CONFIG REQUIRED)

set(SOURCES service.cpp)
set(HEADERS service.h)

add_executable(${USER} user.cpp
        ${SOURCES} ${HEADERS}
)
target_link_libraries(${USER} PRIVATE ${BASIC}
        ${TOOLS}
        mongo::mongocxx_static
        mongo::bsoncxx_static
)

##########################################

set(CLI user.cli)
add_executable(${CLI} user.cli.cpp)
target_link_libraries(${CLI} PRIVATE ${USER}.client
        ${TOOLS}
)