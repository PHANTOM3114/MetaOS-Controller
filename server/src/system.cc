#include "system.hh"

#include <unistd.h>

//Helper Functions

::grpc::Status ProcessingImplemantation::ExecuteShell(::grpc::ServerContext* context, ::grpc::ServerReaderWriter< ::MetaOS::ExecuteShellResponse, ::MetaOS::ExecuteShellRequest>* stream)
{
    MetaOS::ExecuteShellRequest request;
    std::string shell_prompt = request.command();
    std::vector<std::string> black_list = {"reboot", "rm", "sudo", "echo"};

    for (const auto& dangerous_cmd: black_list)
    {
        if (shell_prompt.contains(dangerous_cmd))
        {
            MetaOS::ExecuteShellResponse response;
            response.set_output("Dangerous command");
            response.set_success(false);
            stream->Write(response);
            return ::grpc::Status::OK;
        }
    }

    std::unique_ptr<FILE, decltype(&pclose)> pipe(popen(shell_prompt.c_str(), "r"), pclose);
    if (!pipe) {
        return grpc::Status(grpc::StatusCode::INTERNAL, "popen() failed!");
    }

    while (stream->Read(&request)) {
        std::unique_lock<std::mutex> lock(mutex_);
        while (fgets(buffer.data(), buffer.size(), pipe.get()) != nullptr) {

            MetaOS::ExecuteShellResponse response;
            response.set_output(buffer.data());
            response.set_success(true);
            stream->Write(response);
        }
    }
    return ::grpc::Status::OK;
}