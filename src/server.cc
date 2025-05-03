#include "system.hh"

int main()
{
    ProcessingImplemantation service;
    grpc::ServerBuilder builder;
    builder.AddListeningPort("0.0.0.0:99999", grpc::InsecureServerCredentials());
    builder.RegisterService(&service);

    std::unique_ptr<grpc::Server> server(builder.BuildAndStart());

    server->Wait();

    return 0;
}