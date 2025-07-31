add_executable(client
        src/main.cc
        src/client_system.cc
)

target_include_directories(client PRIVATE
        include
)

target_link_libraries(client PRIVATE
        generated_protos
        gRPC::grpc++
        protobuf::libprotobuf
)