#include <iostream>
#include <memory>
#include <string>
#include <thread>
#include <grpcpp/grpcpp.h>

#include "client_system.hh"
#include "system.grpc.pb.h"

using MetaOS::ExecuteShellRequest;
using MetaOS::ExecuteShellResponse;
using MetaOS::ShellControllerService;

int main(int argc, char** argv) {
    std::string server_address("metaos-server:50051");
    ShellClient client(grpc::CreateChannel(server_address, grpc::InsecureChannelCredentials()));

    std::cout << "[INFO] Connecting to MetaOS server... Type 'exit' to quit." << std::endl;

    client.StartSession();

    std::cout << "[INFO] Session finished. Exiting." << std::endl;

    return 0;
}