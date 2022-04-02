find_package(Drogon CONFIG REQUIRED)

set(SOURCES src/Gateway.cpp src/User.cpp src/Filters.cpp src/AccountAPI.cpp)
set(HEADERS include/Gateway.hpp include/User.hpp include/Filters.hpp include/AccountAPI.hpp)
add_executable(${EXE_10} ${SOURCES} ${HEADERS})
target_include_directories(${EXE_10} PRIVATE include ..)
target_link_libraries(${EXE_10} PRIVATE Drogon::Drogon)