if (DEFINED ENV{DOCKER_ENV})
    cmake_minimum_required(VERSION 3.21)
    project(${PROJECT_NAME} CXX)
endif ()

set(DIRECTORIES "examples/drogon_examples"
                "examples/kafka_examples"
                "examples/mongodb_examples"
                "examples/postgresql_examples"
                "examples/rpc_examples"

                "services/BasicMicroservice"
                "services/Account"
                "services/User"
                "services/Gateway"
                "services/Auth"
                "services/Transaction"
)

foreach(DIR IN LISTS DIRECTORIES)
    string(REPLACE "/" "_" GUARD "${DIR}")
    if (NOT DEFINED ENV{DOCKER_ENV} OR DEFINED ENV{${GUARD}})
        message("<:> ADD_SUBDIRECTORY: ${DIR}")
        add_subdirectory("${DIR}")
    endif()
endforeach()