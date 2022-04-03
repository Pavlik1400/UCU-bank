find_package(rpclib CONFIG REQUIRED)

add_executable(${EXE_12}_server src/rpc_server.cpp)
target_include_directories(${EXE_12}_server PRIVATE ${RPCLIB_INCLUDE_DIR})
target_link_libraries(${EXE_12}_server PRIVATE rpclib::rpc)

add_executable(${EXE_12}_client src/rpc_client.cpp)
target_include_directories(${EXE_12}_client PRIVATE ${RPCLIB_INCLUDE_DIR})
target_link_libraries(${EXE_12}_client PRIVATE rpclib::rpc)
