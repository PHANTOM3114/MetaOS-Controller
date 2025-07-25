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
    ShellReactor() {
        std::cout << "ShellReactor\n";

        epoll_fd_ = epoll_create1(0);
        if (epoll_fd_ == -1) {
            throw std::runtime_error("Failed to create epoll instance: " + std::string(strerror(errno)));
        }

        pid_ = forkpty(&master_fd_,nullptr, nullptr, nullptr);
        if (pid_ == -1) {
            close(epoll_fd_);
            throw std::runtime_error("Failed to forkpty: " + std::string(strerror(errno)));
        }

        if (pid_ == 0) {
            execlp("bash", "bash", nullptr);
            perror("execlp failed");
            exit(1);
        }

        epoll_event event{};
        event.events = EPOLLIN;
        event.data.fd = master_fd_;

        if (epoll_ctl(epoll_fd_, EPOLL_CTL_ADD, master_fd_, &event) == -1) {
            close(master_fd_);
            close(epoll_fd_);
            waitpid(pid_, nullptr, 0);
            throw std::runtime_error("Failed to epoll_ctl: " + std::string(strerror(errno)));
        }

        epoll_cycle = std::thread([&]() {
            std::cout << "Epoll_cycle\n";
            epoll_event events[10];
            while (running_ == true) {
                std::cout << "while cycle in epoll_cycle\n";
                int nfds = epoll_wait(epoll_fd_, events, 10, -1);
                if (nfds == -1) {
                    std::cerr << "epoll_wait error\n";
                    break;
                }

                for (int i = 0; i < nfds; ++i) {
                    if (events[i].data.fd == master_fd_) {
                        char buffer[1024];
                        ssize_t count = read(master_fd_, buffer, sizeof(buffer));
                        if (count == -1) {
                            if (errno != EAGAIN) {
                                std::unique_lock<std::mutex> lock(queue_mutex_);
                                shell_output_queue_.push("");
                                data_notifier.notify_one();
                            }
                        }
                        else if (count == 0) {
                            std::unique_lock<std::mutex> lock(queue_mutex_);
                            shell_output_queue_.push("");
                            data_notifier.notify_one();
                            break;
                        }
                        else {
                            std::string shell_data(buffer, count);
                                {
                                    std::unique_lock<std::mutex> lock(queue_mutex_);
                                    shell_output_queue_.push(shell_data);
                                }
                                data_notifier.notify_one();
                                DoNextWrite();
                        }
                    }
                }
            }
        });
    }
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
