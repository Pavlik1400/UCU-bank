find_package(serdepp CONFIG)
find_package(redis++ CONFIG REQUIRED)
find_package(rpclib CONFIG REQUIRED)
find_package(mongocxx CONFIG REQUIRED)
find_package(bsoncxx CONFIG REQUIRED)
find_package(Boost REQUIRED log)
find_package(nlohmann_json CONFIG REQUIRED)

set(SOURCES service.cpp)
set(HEADERS service.h)

add_executable(${EXE_09} user.cpp
        ${BASIC_SOURCES} ${BASIC_HEADERS}
        ${USER_SOURCES} ${USER_HEADERS}
        ${TOOLS_SOURCES} ${TOOLS_HEADERS}
        ${SOURCES} ${HEADERS}
        )

target_include_directories(${EXE_09} PRIVATE
        ${BASIC_INCLUDE_DIRECTORIES}
        ${USER_INCLUDE_DIRECTORIES}
        ${ROOT_INCLUDE_DIRECTORIES}
        )


target_link_libraries(${EXE_09} PRIVATE
        ${BASIC_INCLUDE_DEP_LIBRARIES}
        ${USER_INCLUDE_DEP_LIBRARIES}
        )

##########################################

set(CLI user.cli)

add_executable(${CLI} user.cli.cpp
        ${USER_SOURCES} ${USER_HEADERS}
        ${TOOLS_SOURCES} ${TOOLS_HEADERS}
        )

target_include_directories(${CLI} PRIVATE
        ${ROOT_INCLUDE_DIRECTORIES}
        )

target_link_libraries(${CLI} PRIVATE
        ${BASIC_INCLUDE_DEP_LIBRARIES}
        )

