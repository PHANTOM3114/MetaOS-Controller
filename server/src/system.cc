#include "system.hh"

#include <unistd.h>

//Helper Functions

::grpc::Status ProcessingImplemantation::ExecuteShell(::grpc::ServerContext* context, const ::MetaOS::ExecuteShellRequest* request, ::grpc::ServerWriter< ::MetaOS::ExecuteShellResponse>* writer)
{
    std::string shell_prompt = request->command();
    std::vector<std::string> black_list = {"reboot", "rm", "sudo", "echo"};

    for (const auto& dangerous_cmd: black_list)
    {
        if (shell_prompt.contains(dangerous_cmd))
        {
            return ::grpc::Status::CANCELLED;
        }
    }

    std::array<char, 128> buffer;
    std::unique_ptr<FILE, decltype(&pclose)> pipe(popen(shell_prompt.c_str(), "r"), pclose);
    if (!pipe) {
        return grpc::Status(grpc::StatusCode::INTERNAL, "popen() failed!");
    }

    while (fgets(buffer.data(), buffer.size(), pipe.get()) != nullptr) {
        MetaOS::ExecuteShellResponse response;
        response.set_output(buffer.data());
        response.set_success(true);
        writer->Write(response);
    }
    return ::grpc::Status::OK;
}