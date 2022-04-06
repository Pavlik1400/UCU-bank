cmake_minimum_required(VERSION 3.21)
project(${PROJECT_NAME} CXX)

set(DIRECTORIES "examples/drogon_examples"
                "examples/kafka_examples"
                "examples/mongodb_examples"
                "examples/postgresql_examples"
                "examples/rpc_examples"

                "src/BasicMicroservice"
                "src/Account"
                "src/User"
                "src/Gateway"
                "src/Auth"
)

foreach(DIR IN LISTS DIRECTORIES)
    string(REPLACE "/" "_" GUARD "${DIR}")
    if (DEFINED ENV{${GUARD}})
        message("<:> ADD_SUBDIRECTORY: ${DIR}")
        add_subdirectory("${DIR}")
    endif()
endforeach()