#include "system.hh"

::grpc::Status ProcessingImplemantation::ShutdownSystemRequest(::grpc::ServerContext* context, const ::MetaOS::ShutdownSystem& request, ::MetaOS::Response* response)
{
    bool result = std::system("echo ShutdownSystemRequest");
    response->set_output("ShutdownSystemRequest");
    response->set_success(result == 0);
    return ::grpc::Status::OK;
}

::grpc::Status ProcessingImplemantation::RunShellScriptRequest(::grpc::ServerContext* context, const ::MetaOS::RunShellScript& request, ::MetaOS::Response* response)
{
    bool result = std::system("echo RunShellScriptRequest");
    response->set_output("RunShellScriptRequest");
    response->set_success(result == 0);
    return ::grpc::Status::OK;
}

::grpc::Status ProcessingImplemantation::OpenAppRequest(::grpc::ServerContext* context, const ::MetaOS::OpenApp& request, ::MetaOS::Response* response)
{
    bool result = std::system("echo OpenAppRequest");
    response->set_output("OpenAppRequest");
    response->set_success(result == 0);
    return ::grpc::Status::OK;
}