set(DIRECTORIES
        "services/basic"
        "services/account"
        "services/user"
        "services/gateway"
        "services/transaction"
        "services/auth"
        "services/notification"
)

if (${MAKE_EXAMPLES})
    set(DIRECTORIES ${DIRECTORIES}
            "examples/drogon_examples"
            "examples/kafka_examples"
            "examples/mongodb_examples"
            "examples/postgresql_examples"
            "examples/rpc_examples"
    )
endif ()

add_subdirectory("config")
foreach (DIR IN LISTS DIRECTORIES)
    add_subdirectory("${DIR}")
endforeach ()