#pragma once

#include <grpcpp/grpcpp.h>
#include "proto/system.grpc.pb.h"
#include "proto/system.pb.h"

// ProcessingImplemantation class, which will handle command and delegate their to machine, on which server is running

class ProcessingImplemantation : public MetaOS::MetaControl::Service
{
public:
    ::grpc::Status ShutdownSystemRequest(::grpc::ServerContext* context, const ::MetaOS::ShutdownSystem& request, ::MetaOS::Response* response);
    ::grpc::Status RunShellScriptRequest(::grpc::ServerContext* context, const ::MetaOS::RunShellScript& request, ::MetaOS::Response* response);
    ::grpc::Status OpenAppRequest(::grpc::ServerContext* context, const ::MetaOS::OpenApp& request, ::MetaOS::Response* response);
};