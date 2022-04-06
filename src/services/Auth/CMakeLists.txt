find_package(aws-cpp-sdk-email REQUIRED)
find_package(ZLIB REQUIRED)

add_executable(${EXE_11} main.cpp src/email/MailSender.cpp)
target_include_directories(${EXE_11} PRIVATE aws-cpp-sdk-email include)
target_link_libraries(${EXE_11} PRIVATE aws-cpp-sdk-email)