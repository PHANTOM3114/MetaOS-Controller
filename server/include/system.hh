#pragma once

#include <grpcpp/grpcpp.h>
#include "system.grpc.pb.h"
#include "system.pb.h"

#include <mutex>
#include <thread>
#include <string>
#include <array>

#include <fcntl.h>
#include <unistd.h>
#include <sys/epoll.h>

class ShellReactor : public grpc::ServerBidiReactor<MetaOS::ExecuteShellRequest, MetaOS::ExecuteShellResponse> {
public:
    explicit ShellReactor() {
        StartRead(&request_);
    }
    void OnReadDone(bool ok) override;
    void OnWriteDone(bool ok) override;
    void OnDone() override;

private:
    MetaOS::ExecuteShellRequest request_;
    MetaOS::ExecuteShellResponse response_;

    void DoNextWrite() {
        char buffer[256];
        if (fgets(buffer, sizeof(buffer), pipe_) != nullptr) {
            response_.set_output(buffer);
            response_.set_success(true);
            StartWrite(&response_);
        }
        else {
            pclose(pipe_);
            pipe_ = nullptr;
            StartRead(&request_);
        }
    }

    FILE* pipe_ = nullptr;

};
class ProcessingImplemantation : public MetaOS::ShellControllerService::CallbackService
{
public:
    grpc::ServerBidiReactor<MetaOS::ExecuteShellRequest, MetaOS::ExecuteShellResponse>* ExecuteShell(grpc::CallbackServerContext* context) override {
        return new ShellReactor();
    }
};


