cmake_minimum_required(VERSION 3.20)
project(remote_contoller)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

find_package(Protobuf REQUIRED CONFIG)
find_package(gRPC CONFIG REQUIRED)

include_directories(${CMAKE_SOURCE_DIR}/server/test)
include_directories(${CMAKE_SOURCE_DIR}/server/include)

include_directories(${CMAKE_SOURCE_DIR}/client/include)

add_library(protolib proto/system.proto)
target_link_libraries(protolib gRPC::grpc++)
target_link_libraries(protolib gRPC::grpc++_reflection)
target_include_directories(protolib PUBLIC ${CMAKE_CURRENT_BINARY_DIR})
get_target_property(grpc_cpp_plugin_location gRPC::grpc_cpp_plugin LOCATION)

protobuf_generate(TARGET protolib LANGUAGE cpp)
protobuf_generate(TARGET protolib LANGUAGE grpc
        GENERATE_EXTENSIONS .grpc.pb.h .grpc.pb.cc
        PLUGIN "protoc-gen-grpc=${grpc_cpp_plugin_location}")

if(CMAKE_CURRENT_SOURCE_DIR STREQUAL CMAKE_SOURCE_DIR)
    option(system_test "build tests (or no)" ON)

    if(system_test)
        enable_testing()
        add_subdirectory(server/test)
    endif()
endif()

add_subdirectory(server)
add_subdirectory(client)

target_link_libraries(server PUBLIC protolib)
target_link_libraries(client PUBLIC protolib)