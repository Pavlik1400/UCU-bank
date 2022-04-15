cmake_minimum_required(VERSION 3.21)
project(${PROJECT_NAME} CXX)


if ("${CMAKE_BUILD_TYPE}" STREQUAL "Debug")
    add_compile_definitions(DEBUG=1)
endif ()
add_subdirectory(src)
execute_process(
    COMMAND ${CMAKE_COMMAND} -E copy ${CMAKE_BINARY_DIR}/compile_commands.json ${CMAKE_SOURCE_DIR}
    ERROR_QUIET
)