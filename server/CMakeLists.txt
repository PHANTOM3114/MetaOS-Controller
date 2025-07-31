add_library(server_logic
        src/system.cc
)

target_include_directories(server_logic PUBLIC
        include
)

target_link_libraries(server_logic PUBLIC
        generated_protos
        gRPC::grpc++
        protobuf::libprotobuf
)

add_executable(server
        src/main.cc
)

target_link_libraries(server PRIVATE
        server_logic
        gRPC::grpc++_reflection
)

option(BUILD_SERVER_TESTS "Build the tests for the server" ON)

if(BUILD_SERVER_TESTS)
    add_subdirectory(test)
endif()