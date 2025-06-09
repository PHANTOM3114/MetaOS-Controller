cmake_minimum_required(VERSION 3.20)
project(server)

include_directories(${CMAKE_SOURCE_DIR}/include)

add_executable(server
        src/system.cc
        src/server.cc
)

target_include_directories(server PRIVATE ../../proto)
target_link_libraries(server PRIVATE protolib)
