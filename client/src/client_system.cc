//
// Created by Mykhailo Khymochko on 10.06.25.
//
#include "client_system.hh"

MetaClient::MetaClient(std::shared_ptr<grpc::Channel> channel)
    : stub_(MetaOS::ShellControllerService::NewStub(channel)) {}

void MetaClient::ExecuteShellRequest() {
    grpc::ClientContext context;

    std::shared_ptr<grpc::ClientReaderWriter<MetaOS::ExecuteShellRequest, MetaOS::ExecuteShellResponse>> stream(stub_->ExecuteShell(&context));

    std::thread writer([stream]() {
        std::string line;
        while (std::getline(std::cin, line)) {
            if (line == "exit") {
                break;
            }

            MetaOS::ExecuteShellRequest request;
            request.set_command(line);

            if (!stream->Write(request)) {
                break;
            }
        }

        stream->WritesDone();
    });

    MetaOS::ExecuteShellResponse response;
    while (stream->Read(&response)) {
        std::cout << response.output();
    }

    writer.join();

    grpc::Status status = stream->Finish();
    if (!status.ok()) {
        std::cerr << "RPC failed: " << status.error_message() << std::endl;
    } else {
        std::cout << "\n--- RPC finished successfully ---\n";
    }
}