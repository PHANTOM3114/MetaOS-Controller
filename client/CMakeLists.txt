cmake_minimum_required(VERSION 3.20)
project(client)

add_executable(client
        src/client.cc
        src/client_system.cc
)

target_include_directories(client PRIVATE ${CMAKE_SOURCE_DIR}/proto ${CMAKE_CURRENT_SOURCE_DIR}/include)
target_link_libraries(client PRIVATE protolib)