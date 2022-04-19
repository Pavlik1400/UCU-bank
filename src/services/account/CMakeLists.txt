find_package(serdepp CONFIG)
find_package(redis++ CONFIG REQUIRED)
find_package(rpclib CONFIG REQUIRED)
find_package(mongocxx CONFIG REQUIRED)
find_package(bsoncxx CONFIG REQUIRED)
find_package(Boost REQUIRED log)
find_package(nlohmann_json CONFIG REQUIRED)

set(SOURCES service.cpp utils.cpp)
set(HEADERS service.h utils.h)

add_executable(${EXE_08} account.cpp
        ${BASIC_SOURCES} ${BASIC_HEADERS}
        ${USER_SOURCES} ${USER_HEADERS}
        ${TOOLS_SOURCES} ${TOOLS_HEADERS}
        ${SOURCES} ${HEADERS}
        )

target_include_directories(${EXE_08} PRIVATE
        ${BASIC_INCLUDE_DIRECTORIES}
        ${USER_INCLUDE_DIRECTORIES}
        ${ROOT_INCLUDE_DIRECTORIES}
        )


target_link_libraries(${EXE_08} PRIVATE
        ${BASIC_INCLUDE_DEP_LIBRARIES}
        ${ACCOUNT_INCLUDE_DEP_LIBRARIES}
        )

##########################################

set(CLI account.cli)

add_executable(${CLI} account.cli.cpp
        ${ACCOUNT_SOURCES} ${ACCOUNT_HEADERS}
        ${TOOLS_SOURCES} ${TOOLS_HEADERS}
        )

target_include_directories(${CLI} PRIVATE
        ${ROOT_INCLUDE_DIRECTORIES}
        )

target_link_libraries(${CLI} PRIVATE
        ${BASIC_INCLUDE_DEP_LIBRARIES}
        )


