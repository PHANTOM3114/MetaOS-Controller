#include "system.hh"

#include <fcntl.h>
#include <unistd.h>
#include <sys/epoll.h>

//Helper Functions
int make_non_blocking(int fd) {
    int flags = fcntl(fd, F_GETFL, 0);
    return fcntl(fd, F_SETFL, flags | O_NONBLOCK);
}

// ::grpc::Status ProcessingImplemantation::ExecuteShell(::grpc::ServerContext* context, ::grpc::ServerReaderWriter< ::MetaOS::ExecuteShellResponse, ::MetaOS::ExecuteShellRequest>* stream)
// {
//     MetaOS::ExecuteShellRequest request;
//     std::string shell_prompt = request.command();
//     std::vector<std::string> black_list = {"reboot", "rm", "sudo", "echo"};
//
//     int epoll_fd = epoll_create1(0);
//     if (epoll_fd == -1) {
//         std::cerr << "epoll_create1 failed\n";
//     }
//
//     // Робимо stdin неблокуючим
//     make_non_blocking(STDIN_FILENO);
//
//     epoll_event event{};
//     event.events = EPOLLIN;
//     event.data.fd = STDIN_FILENO;
//
//     if (epoll_ctl(epoll_fd, EPOLL_CTL_ADD, STDIN_FILENO, &event) == -1) {
//         std::cerr << "epoll_ctl failed\n";
//     }
//     epoll_event events[10];
//
//     while (true) {
//         int nfds = epoll_wait(epoll_fd, events, 10, -1); // -1 = чекати вічно
//         if (nfds == -1) {
//             std::cerr << "epoll_wait error\n";
//             break;
//         }
//
//         for (int i = 0; i < nfds; ++i) {
//             if (events[i].data.fd == STDIN_FILENO) {
//                 char buffer[1024];
//                 ssize_t count = read(STDIN_FILENO, buffer, sizeof(buffer));
//                 if (count == -1) {
//                     if (errno != EAGAIN) {
//                         std::cerr << "read error\n";
//                     }
//                 }
//                 else if (count == 0) {
//                     std::cout << "EOF\n";
//                 }
//                 else {
//
//                 }
//             }
//         }
//     }
//
//     close(epoll_fd);
//
//     std::unique_ptr<FILE, decltype(&pclose)> pipe(popen(shell_prompt.c_str(), "r"), pclose);
//     if (!pipe) {
//         return grpc::Status(grpc::StatusCode::INTERNAL, "popen() failed!");
//     }
//
//     while (stream->Read(&request)) {
//         std::unique_lock<std::mutex> lock(mutex_);
//         while (fgets(buffer.data(), buffer.size(), pipe.get()) != nullptr) {
//
//             MetaOS::ExecuteShellResponse response;
//             response.set_output(buffer.data());
//             response.set_success(true);
//             stream->Write(response);
//         }
//     }
//
//     return ::grpc::Status::OK;
// }

void ShellReactor::OnReadDone(bool ok) override {
    if (ok) {
        std::cout << "OnReadDone" << std::endl;
        std::string command = request_.command();
        pipe_ = popen(command.c_str(), "r");
        if (!pipe_) {
            std::cout << "Pipe Error" << std::endl;
            Finish(grpc::Status(grpc::StatusCode::INTERNAL, "Failed to popen"));
            return;
        }
        DoNextWrite();
    }
    else {
        std::cout << "OnReadDone Finish" << std::endl;
        Finish(grpc::Status::OK);
    }
}

void ShellReactor::OnWriteDone(bool ok) override {
    if (ok) {
        std::cout << "OnWriteDone" << std::endl;
        DoNextWrite();
    } else {
        std::cout << "Pipe Closing" << std::endl;
        if (pipe_) {
            pclose(pipe_);
            pipe_ = nullptr;
        }
        Finish(grpc::Status::CANCELLED);
    }
}

void ShellReactor::OnDone() override {
    std::cout << "OnDone" << std::endl;
    if (pipe_) {
        pclose(pipe_);
    }
    delete this;
}