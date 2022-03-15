find_package(mongocxx CONFIG REQUIRED)
find_package(bsoncxx CONFIG REQUIRED)

add_executable(${EXE_04} src/usage_overview.cpp)
target_include_directories(${EXE_04} PRIVATE ${LIBMONGOCXX_INCLUDE_DIR})
target_include_directories(${EXE_04} PRIVATE ${LIBBSONCXX_INCLUDE_DIR})
target_link_libraries(${EXE_04} mongo::mongocxx_static mongo::bsoncxx_static)


