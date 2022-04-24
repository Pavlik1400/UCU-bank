find_package(aws-cpp-sdk-email REQUIRED)
find_package(ZLIB REQUIRED)
find_package(rpclib CONFIG REQUIRED)
find_package(Boost REQUIRED log program_options)
find_package(redis++ CONFIG REQUIRED)
find_package(libpqxx CONFIG REQUIRED)
find_package(serdepp CONFIG)
find_package(nlohmann_json CONFIG REQUIRED)
find_package(mongocxx CONFIG REQUIRED)
find_package(bsoncxx CONFIG REQUIRED)


set(AUTH_ENTRY_POINT main.cpp)

# add_executable(${EXE_11} main.cpp src/email/MailSender.cpp)
# target_include_directories(${EXE_11} PRIVATE aws-cpp-sdk-email include)
# target_link_libraries(${EXE_11} PRIVATE aws-cpp-sdk-email)

add_executable(${EXE_11} auth.cpp
    ${AUTH_SOURCES} ${AUTH_HEADERS}
    ${BASIC_SOURCES} ${BASIC_HEADERS}
    ${ACCOUNT_SOURCES} ${ACCOUNT_HEADERS}
    ${USER_SOURCES} ${USER_HEADERS}
    ${TOOLS_SOURCES} ${TOOLS_HEADERS}
    email/MailSender.cpp email/MailSender.h 
)

add_executable(${EXE_11}.test auth.test.cpp
    ${AUTH_SOURCES} ${AUTH_HEADERS}
    ${BASIC_SOURCES} ${BASIC_HEADERS}
    ${ACCOUNT_SOURCES} ${ACCOUNT_HEADERS}
    ${USER_SOURCES} ${USER_HEADERS}
    ${TOOLS_SOURCES} ${TOOLS_HEADERS}
    email/MailSender.cpp email/MailSender.h 
)

add_executable(${EXE_11}.cli client.cli.cpp
    ${TOOLS_SOURCES} ${TOOLS_HEADERS}
    client.cpp client.hpp 
)

message("BASIC_INCLUDE_DIRECTORIES: ${BASIC_INCLUDE_DIRECTORIES}")

target_include_directories(${EXE_11} PRIVATE 
    ${AUTH_INCLUDE_DIRECTORIES}
    ${BASIC_INCLUDE_DIRECTORIES}
    ${ACCOUNT_INCLUDE_DIRECTORIES}
    ${USER_INCLUDE_DIRECTORIES}
    ${ROOT_INCLUDE_DIRECTORIES}
    aws-cpp-sdk-email
    email
)

target_include_directories(${EXE_11}.test PRIVATE 
    ${AUTH_INCLUDE_DIRECTORIES}
    ${BASIC_INCLUDE_DIRECTORIES}
    ${ACCOUNT_INCLUDE_DIRECTORIES}
    ${USER_INCLUDE_DIRECTORIES}
    ${ROOT_INCLUDE_DIRECTORIES}
    aws-cpp-sdk-email
    email
)

target_include_directories(${EXE_11}.cli PRIVATE 
    ${BASIC_INCLUDE_DIRECTORIES}
    ${ROOT_INCLUDE_DIRECTORIES}
)

message("${ROOT_INCLUDE_DIRECTORIES}")

target_link_libraries(${EXE_11} PRIVATE 
    ${BASIC_INCLUDE_DEP_LIBRARIES}
    ${ACCOUNT_INCLUDE_DEP_LIBRARIES}
    ${USER_INCLUDE_DEP_LIBRARIES}
    aws-cpp-sdk-email
)

target_link_libraries(${EXE_11}.test PRIVATE 
    ${BASIC_INCLUDE_DEP_LIBRARIES}
    ${ACCOUNT_INCLUDE_DEP_LIBRARIES}
    ${USER_INCLUDE_DEP_LIBRARIES}
    aws-cpp-sdk-email
)

target_link_libraries(${EXE_11}.cli PRIVATE 
    ${BASIC_INCLUDE_DEP_LIBRARIES}
    Boost::program_options
)