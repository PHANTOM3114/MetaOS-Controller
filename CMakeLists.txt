cmake_minimum_required(VERSION 3.20)
project(gRPC_server)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

find_package(Protobuf REQUIRED CONFIG)  
find_package(gRPC CONFIG REQUIRED)

include_directories(${CMAKE_SOURCE_DIR}/include)

add_library(protolib proto/system.proto)
target_link_libraries(protolib gRPC::grpc++)
target_include_directories(protolib PUBLIC ${CMAKE_CURRENT_BINARY_DIR})
get_target_property(grpc_cpp_plugin_location gRPC::grpc_cpp_plugin LOCATION)

protobuf_generate(TARGET protolib LANGUAGE cpp)
protobuf_generate(TARGET protolib LANGUAGE grpc
GENERATE_EXTENSIONS .grpc.pb.h .grpc.pb.cc
PLUGIN "protoc-gen-grpc=${grpc_cpp_plugin_location}")

add_executable(server src/server.cc
                      src/system.cc)
target_link_libraries(server protolib)
