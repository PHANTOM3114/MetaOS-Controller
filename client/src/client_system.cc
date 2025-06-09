//
// Created by Mykhailo Khymochko on 10.06.25.
//
#include "client_system.hh"

MetaClient::MetaClient(std::shared_ptr<grpc::Channel> channel)
    : stub_(MetaOS::MetaControl::NewStub(channel)) {}

MetaOS::Response MetaClient::RunShellScript(const std::string& command) {
    MetaOS::RunShellScript request;
    request.set_command(command);

    MetaOS::Response response;
    grpc::ClientContext context;

    grpc::Status status = stub_->RunShellScriptRequest(&context, request, &response);

    if (!status.ok()) {
        std::cerr << "RPC failed: " << status.error_message() << std::endl;
        response.set_output("RPC failed");
        response.set_success(false);
    }

    return response;
}