//
// Created by Mykhailo Khymochko on 10.06.25.
//
#include "client_system.hh"

MetaClient::MetaClient(std::shared_ptr<grpc::Channel> channel)
    : stub_(MetaOS::ShellControllerService::NewStub(channel)) {}

void MetaClient::ExecuteShellRequest(const std::string& command) {
    grpc::ClientContext context;
    MetaOS::ExecuteShellRequest request;
    MetaOS::ExecuteShellResponse response;

    request.set_command(command);

    std::unique_ptr<grpc::ClientReader<::MetaOS::ExecuteShellResponse>> reader(stub_->ExecuteShell(&context, request));

    while (reader->Read(&response)) {
        std::cout << response.output() << std::endl;
    }

    grpc::Status status = reader->Finish();
}