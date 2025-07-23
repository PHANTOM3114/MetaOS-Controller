//Standard includes
#include <iostream>
#include <memory>
#include <string>

//gRPC includes
#include <grpcpp/ext/proto_server_reflection_plugin.h>
#include <grpcpp/grpcpp.h>
#include <system.grpc.pb.h>

#include <system.hh>

using grpc::Server;
using grpc::ServerBuilder;
using grpc::ServerContext;
using grpc::Status;
using MetaOS::ExecuteShellRequest;
using MetaOS::ExecuteShellResponse;

// class EchoReactor : public grpc::ServerBidiReactor<MetaOS::EchoRequest, MetaOS::EchoResponse> {
// public:
//     EchoReactor() {
//         std::cout << "[EchoReactor] New session created. Waiting for the first message...\n";
//         StartRead(&request_);
//     }
//
//     void OnReadDone(bool ok) override {
//         if (ok) {
//             std::cout << "[EchoReactor] Received message: " << request_.message() << "\n";
//             response_.set_message(request_.message());
//             StartWrite(&response_);
//         }
//         else {
//             std::cout << "[EchoReactor] Client disconnected.\n";
//             Finish(grpc::Status::OK);
//         }
//     };
//     void OnWriteDone (bool ok) override {
//         if (ok) {
//             std::cout << "[EchoReactor] Reply sent successfully. Waiting for the next message...\n";
//             StartRead(&request_);
//         }
//         else if (message_count >= 3) {
//             std::cout << "[EchoReactor] Write failed.\n";
//             Finish(grpc::Status::CANCELLED);
//         }
//     }
//
//     void OnDone() override {
//         std::cout << "[EchoReactor] Session is done. Deleting reactor.\n";
//         delete this;
//     }
// private:
//     int message_count = 0;
//     MetaOS::EchoRequest request_;
//     MetaOS::EchoResponse response_;
// };
//
// class EchoServiceImpl final : public MetaOS::EchoService::CallbackService {
// public:
//     grpc::ServerBidiReactor<MetaOS::EchoRequest, MetaOS::EchoResponse>* DoEcho(
//         grpc::CallbackServerContext* context) override {
//         std::cout << "[EchoService] A new client is connecting. Creating a reactor for it...\n";
//         return new EchoReactor();
//     }
// };

int main(int argc, char** argv) {

    grpc::reflection::InitProtoReflectionServerBuilderPlugin();

    ProcessingImplemantation service;
    ServerBuilder builder;

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
