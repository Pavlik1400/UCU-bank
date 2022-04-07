find_package(Drogon CONFIG REQUIRED)

set(SOURCES src/Gateway.cpp src/UserAPI.cpp src/Filters.cpp src/AccountAPI.cpp src/api_utlis.cpp)
set(HEADERS include/Gateway.hpp include/UserAPI.hpp include/Filters.hpp include/AccountAPI.hpp include/api_utlis.hpp)
add_executable(${EXE_10} ${SOURCES} ${HEADERS})
target_include_directories(${EXE_10} PRIVATE include ..)
target_link_libraries(${EXE_10} PRIVATE Drogon::Drogon)