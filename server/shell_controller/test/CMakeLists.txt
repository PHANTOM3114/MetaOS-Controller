include(FetchContent)
FetchContent_Declare(
        googletest
        URL https://github.com/google/googletest/archive/03597a01ee50ed33e9dfd640b249b4be3799d395.zip
)

FetchContent_MakeAvailable(googletest)

include_directories(../include)

add_executable(server_tests
        system_test.cc
)

target_link_libraries(server_tests PRIVATE
        gtest_main
        server_logic
        generated_protos
        gRPC::grpc++
        protobuf::libprotobuf
)

include(GoogleTest)
gtest_discover_tests(server_tests)