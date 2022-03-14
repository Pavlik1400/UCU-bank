cmake_minimum_required(VERSION 3.21)
project(${PROJECT_NAME} CXX)

find_package(Drogon CONFIG REQUIRED)

add_subdirectory(examples/drogon_examples)
add_subdirectory(examples/kafka_examples)