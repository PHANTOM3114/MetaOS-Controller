#include <iostream>
#include "client_system.hh"

int main() {
    MetaClient client(grpc::CreateChannel("localhost:50051", grpc::InsecureChannelCredentials()));

    client.ExecuteShellRequest();

    return 0;
}