//
// Created by Mykhailo Khymochko on 10.06.25.
//
#include "client_system.hh"

MetaClient::MetaClient(std::shared_ptr<grpc::Channel> channel)
    : stub_(MetaOS::ShellControllerService::NewStub(channel)) {}

void MetaClient::ExecuteShellRequest(const std::string& command, MetaOS::ExecuteShellResponse* response) {
    MetaOS::ExecuteShellRequest request;
    grpc::ClientContext context;

    request.set_command(command);

    grpc::Status status = stub_->ExecuteShell(&context, request, response);

    if (!status.ok()) {
        std::cerr << "RPC failed: " << status.error_message() << std::endl;
        response->set_output("RPC failed: " + status.error_message());
        response->set_success(false);
    }
}