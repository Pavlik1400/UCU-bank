find_package(mongocxx CONFIG REQUIRED)
find_package(bsoncxx CONFIG REQUIRED)
set(SOURCES src/Account.cpp src/AccountMicroservice.cpp)
set(HEADERS include/Account.h include/AccountType.h include/AccountMicroservice.h ../BasicMicroservice/include)
add_executable(${EXE_08} ${SOURCES} ${HEADERS})
target_include_directories(${EXE_08} PRIVATE ${LIBMONGOCXX_INCLUDE_DIR})
target_include_directories(${EXE_08} PRIVATE ${LIBBSONCXX_INCLUDE_DIR})
target_include_directories(${EXE_08} PRIVATE include ../BasicMicroservice/include)
target_link_libraries(${EXE_08} mongo::mongocxx_static mongo::bsoncxx_static)


