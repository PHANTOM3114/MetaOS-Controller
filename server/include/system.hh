#pragma once

#include <grpcpp/grpcpp.h>
#include "system.grpc.pb.h"
#include "system.pb.h"

#include <mutex>
#include <thread>
// ProcessingImplemantation class, which will handle command and delegate their to machine, on which the server is running

class ProcessingImplemantation : public MetaOS::ShellControllerService::Service
{
public:
    grpc::Status ExecuteShell(::grpc::ServerContext* context, ::grpc::ServerReaderWriter< ::MetaOS::ExecuteShellResponse, ::MetaOS::ExecuteShellRequest>* stream);
private:
    std::array<char, 128> buffer;
    std::mutex mutex_;
};