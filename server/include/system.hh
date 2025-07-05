#pragma once

#include <grpcpp/grpcpp.h>
#include "system.grpc.pb.h"
#include "system.pb.h"

// ProcessingImplemantation class, which will handle command and delegate their to machine, on which the server is running

class ProcessingImplemantation : public MetaOS::ShellControllerService::Service
{
public:
    grpc::Status ExecuteShell(::grpc::ServerContext* context, const ::MetaOS::ExecuteShellRequest* request, ::grpc::ServerWriter< ::MetaOS::ExecuteShellResponse>* writer);
};