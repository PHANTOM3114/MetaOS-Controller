//
// Created by Mykhailo Khymochko on 10.06.25.
//

#pragma once

#include <grpcpp/grpcpp.h>
#include "system.grpc.pb.h"

#include <thread>
#include <mutex>
#include <iostream>

class ShellClient {
public:
    ShellClient(std::shared_ptr<grpc::Channel> channel)
        : stub_(MetaOS::ShellControllerService::NewStub(channel)) {}

    void StartSession();

private:
    std::unique_ptr<MetaOS::ShellControllerService::Stub> stub_;
    std::unique_ptr<grpc::ClientReaderWriter<MetaOS::ExecuteShellRequest, MetaOS::ExecuteShellResponse>> stream_;
    std::thread reader_thread_;
    std::thread writer_thread_;
};