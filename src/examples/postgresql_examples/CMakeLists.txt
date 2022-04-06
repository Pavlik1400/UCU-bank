find_package(libpqxx CONFIG REQUIRED)

add_executable(${EXE_06} src/basic.cpp)
target_link_libraries(${EXE_06} PRIVATE libpqxx::pqxx)