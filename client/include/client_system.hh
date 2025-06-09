//
// Created by Mykhailo Khymochko on 10.06.25.
//

#pragma once

#include <grpcpp/grpcpp.h>
#include "proto/system.grpc.pb.h"

class MetaClient {
public:
    explicit MetaClient(std::shared_ptr<grpc::Channel> channel);

    MetaOS::Response RunShellScript(const std::string& command);

private:
    std::unique_ptr<MetaOS::MetaControl::Stub> stub_;
};
