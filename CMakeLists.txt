cmake_minimum_required(VERSION 3.20)
project(remote_controller CXX)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

find_package(gRPC REQUIRED)

set(PROTO_FILES ${CMAKE_CURRENT_SOURCE_DIR}/proto/system.proto)
set(GENERATED_DIR ${CMAKE_BINARY_DIR}/generated_proto_files)

get_filename_component(PROTO_FILENAME ${PROTO_FILES} NAME_WE)
set(GENERATED_PB_H ${GENERATED_DIR}/${PROTO_FILENAME}.pb.h)
set(GENERATED_PB_CC ${GENERATED_DIR}/${PROTO_FILENAME}.pb.cc)
set(GENERATED_GRPC_H ${GENERATED_DIR}/${PROTO_FILENAME}.grpc.pb.h)
set(GENERATED_GRPC_CC ${GENERATED_DIR}/${PROTO_FILENAME}.grpc.pb.cc)

add_custom_command(
        OUTPUT
        ${GENERATED_PB_H} ${GENERATED_PB_CC}
        ${GENERATED_GRPC_H} ${GENERATED_GRPC_CC}
        COMMAND ${CMAKE_COMMAND} -E make_directory ${GENERATED_DIR}
        COMMAND protobuf::protoc
        --proto_path=${CMAKE_CURRENT_SOURCE_DIR}/proto
        --cpp_out=${GENERATED_DIR}
        --grpc_out=${GENERATED_DIR}
        --plugin=protoc-gen-grpc=$<TARGET_FILE:gRPC::grpc_cpp_plugin>
        ${PROTO_FILES}
        DEPENDS ${PROTO_FILES}
)

add_library(generated_protos
        ${GENERATED_PB_CC}
        ${GENERATED_GRPC_CC}
)

target_include_directories(generated_protos PUBLIC
        ${GENERATED_DIR}
)

target_link_libraries(generated_protos PUBLIC
        protobuf::libprotobuf
        gRPC::grpc++
)

enable_testing()

add_subdirectory(server)
add_subdirectory(client)