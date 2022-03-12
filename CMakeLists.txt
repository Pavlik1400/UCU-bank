cmake_minimum_required(VERSION 3.15)
set(PROJECT_NAME ucubank)
set(APP_NAME ucubank)
project(${PROJECT_NAME} CXX)
set(CMAKE_CXX_STANDARD 17)

# Include config
include(cmake/CMakeLists.txt)

# DROGON
add_subdirectory(${DROGON_SUBDIR_PATH} ${DROGON_SUBDIR_PATH}/build)
set(DROGON_INCLUDE_DIR ${DROGON_SUBDIR_PATH}/lib/inc)

add_subdirectory(libs_examples)