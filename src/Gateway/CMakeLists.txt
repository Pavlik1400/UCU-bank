find_package(Drogon CONFIG REQUIRED)

set(SOURCES src/Gateway.cpp src/User.cpp src/Filters.cpp)
set(HEADERS include/Gateway.h include/User.h include/Filters.h)
add_executable(${EXE_10} ${SOURCES} ${HEADERS})
target_include_directories(${EXE_10} PRIVATE include)
target_link_libraries(${EXE_10} PRIVATE Drogon::Drogon)