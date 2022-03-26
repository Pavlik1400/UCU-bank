find_package(mongocxx CONFIG REQUIRED)
find_package(bsoncxx CONFIG REQUIRED)
set(SOURCES src/User.cpp)
set(HEADERS include/User.h)
add_executable(${EXE_09} ${SOURCES} ${HEADERS})
target_include_directories(${EXE_09} PRIVATE ${LIBMONGOCXX_INCLUDE_DIR})
target_include_directories(${EXE_09} PRIVATE ${LIBBSONCXX_INCLUDE_DIR})
target_include_directories(${EXE_09} PRIVATE include)
target_link_libraries(${EXE_09} mongo::mongocxx_static mongo::bsoncxx_static)


