#include "system.hh"

#include <fcntl.h>
#include <unistd.h>
#include <sys/epoll.h>
#include <sys/wait.h>
#include <termios.h>

void ShellReactor::OnReadDone(bool ok) {
    if (ok) {
        std::cout << "OnReadDone\n";
        std::string shell_prompt = request_.command();
        write(master_fd_, shell_prompt.c_str(), shell_prompt.length());
        StartRead(&request_);
    }
    else {
        Finish(grpc::Status::OK);
    }
}

void ShellReactor::OnWriteDone(bool ok) {
    if (ok) {
        std::cout << "OnWriteDone\n";
        DoNextWrite();
    }
    else {
        OnDone();
        Finish(grpc::Status::CANCELLED);
    }
}

void ShellReactor::DoNextWrite() {
    std::unique_lock<std::mutex> lock(queue_mutex_);
    data_notifier.wait(lock, [&] { return !shell_output_queue_.empty(); });

    std::string data = shell_output_queue_.front();
    shell_output_queue_.pop();

    lock.unlock();

    if (data.empty()) {
        Finish(grpc::Status::OK);
    }
    else {
        response_.set_output(data);
        StartWrite(&response_);
    }
}