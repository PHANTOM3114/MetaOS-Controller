//
// Created by Mykhailo Khymochko on 10.06.25.
//

#pragma once

#include <grpcpp/grpcpp.h>
#include "system.grpc.pb.h"

#include <thread>
#include <mutex>
#include <iostream>

class MetaClient {
public:
    explicit MetaClient(std::shared_ptr<grpc::Channel> channel);

    void ExecuteShellRequest();
private:
    std::unique_ptr<MetaOS::ShellControllerService::Stub> stub_;
};
