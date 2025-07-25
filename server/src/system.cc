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
        std::cout << "After StartRead in OnReadDone\n";
    }
    else {
        Finish(grpc::Status::OK);
    }
}

void ShellReactor::OnWriteDone(bool ok) {
    writing_in_progress_.clear();

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
    if (writing_in_progress_.test_and_set()) {
        return;
    }

    std::unique_lock<std::mutex> lock(queue_mutex_);
    if (shell_output_queue_.empty()) {
        writing_in_progress_.clear();
        return;
    }

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