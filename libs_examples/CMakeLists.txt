set(EXAMPLE_NAME drogon_basic)

add_executable(${EXAMPLE_NAME} src/drogon_basic.cpp include/drogon_basic.h)
target_include_directories(${EXAMPLE_NAME} PRIVATE include ${DROGON_INCLUDE_DIR})
target_link_libraries(${EXAMPLE_NAME} PRIVATE drogon)
set_target_properties(${EXAMPLE_NAME} PROPERTIES RUNTIME_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/bin")