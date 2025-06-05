#include "system.hh"

int main()
{
    ProcessingImplemantation service;
    grpc::ServerBuilder builder;

    // Set the server address and port

    builder.AddListeningPort("0.0.0.0:50051", grpc::InsecureServerCredentials());
    builder.RegisterService(&service);

    // Start the server

    std::unique_ptr<grpc::Server> server(builder.BuildAndStart());

    if (!server) {
        std::cerr << "Failed to start server" << std::endl;
        return -1;
    }
    else {
        std::cout << "Server started on port 50051" << std::endl;
        server->Wait();
    }
    return 0;
}
