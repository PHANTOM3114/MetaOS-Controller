#include <iostream>
#include <memory>
#include <string>
#include <thread>
#include <grpcpp/grpcpp.h>

//#include "client_system.hh"
#include "system.grpc.pb.h"

using MetaOS::ExecuteShellRequest;
using MetaOS::ExecuteShellResponse;
using MetaOS::ShellControllerService;

class ShellClient {
public:
    ShellClient(std::shared_ptr<grpc::Channel> channel)
        : stub_(ShellControllerService::NewStub(channel)) {}

    void StartSession() {

        grpc::ClientContext context;

        stream_ = stub_->ExecuteShell(&context);


        reader_thread_ = std::thread([this]() {
            ExecuteShellResponse response;
            while (stream_->Read(&response)) {
                fwrite(response.output().c_str(), 1, response.output().length(), stdout);
                fflush(stdout);
            }
            std::cout << "\n[INFO] Server disconnected." << std::endl;
        });

        writer_thread_ = std::thread([this]() {
            ExecuteShellRequest request;
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

private:
    std::unique_ptr<ShellControllerService::Stub> stub_;
    std::unique_ptr<grpc::ClientReaderWriter<ExecuteShellRequest, ExecuteShellResponse>> stream_;
    std::thread reader_thread_;
    std::thread writer_thread_;
};

int main(int argc, char** argv) {
    std::string server_address("metaos-server:50051");
    ShellClient client(grpc::CreateChannel(server_address, grpc::InsecureChannelCredentials()));

    std::cout << "[INFO] Connecting to MetaOS server... Type 'exit' to quit." << std::endl;

    client.StartSession();

    std::cout << "[INFO] Session finished. Exiting." << std::endl;

    return 0;
}