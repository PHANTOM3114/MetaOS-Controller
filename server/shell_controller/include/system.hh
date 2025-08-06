#pragma once

#include <grpcpp/grpcpp.h>
#include "system.grpc.pb.h"
#include "system.pb.h"

#include <mutex>
#include <thread>
#include <string>
#include <array>
#include <vector>
#include <queue>
#include <condition_variable>
#include <pty.h>
#include <termios.h>

#include <fcntl.h>
#include <unistd.h>
#include <sys/epoll.h>
#include <sys/wait.h>

class ShellReactor : public grpc::ServerBidiReactor<MetaOS::ExecuteShellRequest, MetaOS::ExecuteShellResponse> {
public:
    ShellReactor();

    void Start() {
        std::cout << "Start\n";
        StartRead(&request_);
    }
    void OnReadDone(bool ok) override;
    void OnWriteDone(bool ok) override;

    void OnDone() override {
        std::cout << "OnDone\n";
        running_ = false;
        close(master_fd_);

        if (epoll_cycle.joinable()) {
            epoll_cycle.join();
        }

        waitpid(pid_, nullptr, 0);
        close(epoll_fd_);

        delete this;
    }

private:
    void DoNextWrite();

    int master_fd_;
    pid_t pid_;
    int epoll_fd_;

    std::thread epoll_cycle;
    std::queue<std::string> shell_output_queue_;
    std::mutex queue_mutex_;
    std::condition_variable data_notifier;
    std::atomic<bool> running_ = true;
    std::atomic_flag writing_in_progress_ = ATOMIC_FLAG_INIT;

    MetaOS::ExecuteShellRequest request_;
    MetaOS::ExecuteShellResponse response_;
};

class AbortedReactor : public grpc::ServerBidiReactor<MetaOS::ExecuteShellRequest, MetaOS::ExecuteShellResponse> {
public:
    explicit AbortedReactor(const grpc::Status& status) {
        Finish(status);
    }

    void OnDone() override { delete this; }
    void OnReadDone(bool ok) override {}
    void OnWriteDone(bool ok) override {}
};

class ProcessingImplemantation : public MetaOS::ShellControllerService::CallbackService
{
public:
    grpc::ServerBidiReactor<MetaOS::ExecuteShellRequest, MetaOS::ExecuteShellResponse>* ExecuteShell(grpc::CallbackServerContext* context) override {
        try {
            auto* reactor = new ShellReactor();
            reactor->Start();
            return reactor;
        }
        catch (const std::exception& e) {
            std::cerr << "Failed to create ShellReactor: " << e.what() << std::endl;
            return new AbortedReactor(grpc::Status(grpc::StatusCode::INTERNAL, e.what()));
        }
    }
};
