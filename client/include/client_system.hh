//
// Created by Mykhailo Khymochko on 10.06.25.
//

#pragma once

#include <grpcpp/grpcpp.h>
#include "system.grpc.pb.h"

class MetaClient {
public:
    explicit MetaClient(std::shared_ptr<grpc::Channel> channel);

    void ExecuteShellRequest(const std::string& command, MetaOS::ExecuteShellResponse* response);
private:
    std::unique_ptr<MetaOS::ShellControllerService::Stub> stub_;
};
