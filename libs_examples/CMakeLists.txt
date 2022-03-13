set(DROGON_BASIC drogon_basic)
set(DROGON_JSON drogon_json)
set(DROGON_REST_API drogon_rest_api)

add_executable(${DROGON_BASIC} src/drogon_basic.cpp include/drogon_basic.h)
target_include_directories(${DROGON_BASIC} PRIVATE include ${DROGON_INCLUDE_DIR})
target_link_libraries(${DROGON_BASIC} PRIVATE drogon)
set_target_properties(${DROGON_BASIC} PROPERTIES RUNTIME_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/bin")


add_executable(${DROGON_JSON} src/drogon_json.cpp include/drogon_json.h)
target_include_directories(${DROGON_JSON} PRIVATE include ${DROGON_INCLUDE_DIR})
target_link_libraries(${DROGON_JSON} PRIVATE drogon)
set_target_properties(${DROGON_JSON} PROPERTIES RUNTIME_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/bin")


add_executable(${DROGON_REST_API} src/drogon_rest_api.cpp include/drogon_rest_api.h)
target_include_directories(${DROGON_REST_API} PRIVATE include ${DROGON_INCLUDE_DIR})
target_link_libraries(${DROGON_REST_API} PRIVATE drogon)
set_target_properties(${DROGON_REST_API} PROPERTIES RUNTIME_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/bin")