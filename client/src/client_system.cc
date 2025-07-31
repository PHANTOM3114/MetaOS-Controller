//
// Created by Mykhailo Khymochko on 10.06.25.
//
#include "client_system.hh"

void ShellClient::StartSession() {

    grpc::ClientContext context;

    stream_ = stub_->ExecuteShell(&context);


    reader_thread_ = std::thread([this]() {
        MetaOS::ExecuteShellResponse response;
        while (stream_->Read(&response)) {
            fwrite(response.output().c_str(), 1, response.output().length(), stdout);
            fflush(stdout);
        }
        std::cout << "\n[INFO] Server disconnected." << std::endl;
    });

    writer_thread_ = std::thread([this]() {
        MetaOS::ExecuteShellRequest request;
        for (std::string command; std::getline(std::cin, command);) {
            if (command == "exit") {
                break;
            }
            request.set_command(command + "\n");
            if (!stream_->Write(request)) {
                std::cerr << "\n[ERROR] Failed to write to server." << std::endl;
                break;
            }
        }
        stream_->WritesDone();
    });

    writer_thread_.join();
    reader_thread_.join();

    grpc::Status status = stream_->Finish();
    if (!status.ok()) {
        std::cerr << "\n[ERROR] RPC failed: " << status.error_code() << ": " << status.error_message() << std::endl;
    }
}