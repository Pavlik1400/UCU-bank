find_package(aws-cpp-sdk-email REQUIRED)
find_package(Boost COMPONENTS program_options REQUIRED)
find_package(ZLIB REQUIRED)

set (SOURCES service.cpp
    email/MailSender.cpp) 
set (HEADERS service.hpp
    email/MailSender.h) 

#####

add_executable(${AUTH} auth.cpp
    ${SOURCES} ${HEADERS}
)
target_link_libraries(${AUTH} PRIVATE  ${BASIC}
    ${USER}.client
    ${TOOLS}
    aws-cpp-sdk-email
)

#####

add_executable(${AUTH}.cli client.cli.cpp)
target_link_libraries(${AUTH}.cli PRIVATE ${AUTH}.client 
    ${USER}.client
    ${TOOLS}
    Boost::program_options
)

#####

add_executable(${AUTH}.test auth.test.cpp)
target_link_libraries(${AUTH}.test PRIVATE ${USER}.client)