add_executable(${EXE_00} src/drogon_basic.cpp include/drogon_basic.h)
target_include_directories(${EXE_00} PRIVATE include)
target_link_libraries(${EXE_00} PRIVATE Drogon::Drogon)

add_executable(${EXE_01} src/drogon_json.cpp include/drogon_json.h)
target_include_directories(${EXE_01} PRIVATE include)
target_link_libraries(${EXE_01} PRIVATE Drogon::Drogon)

add_executable(${EXE_02} src/drogon_rest_api.cpp include/drogon_rest_api.h)
target_include_directories(${EXE_02} PRIVATE include)
target_link_libraries(${EXE_02} PRIVATE Drogon::Drogon)