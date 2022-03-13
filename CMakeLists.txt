cmake_minimum_required(VERSION 3.21)
project(${PROJECT_NAME} CXX)

# DROGON
find_package(Drogon CONFIG REQUIRED)

add_subdirectory(libs_examples)