#include "system.hh"

#include <unistd.h>

::grpc::Status ProcessingImplemantation::ExecuteShell(::grpc::ServerContext* context, const ::MetaOS::ExecuteShellRequest* request, ::MetaOS::ExecuteShellResponse* response)
{
    std::string shell_prompt = request->command();
    std::array<char, 128> buffer;
    std::string result;
    std::unique_ptr<FILE, decltype(&pclose)> pipe(popen(shell_prompt.c_str(), "r"), pclose);
    if (!pipe) {
        throw std::runtime_error("popen() failed!");
    }
    while (fgets(buffer.data(), static_cast<int>(buffer.size()), pipe.get()) != nullptr) {
        result += buffer.data();
    }

    response->set_output(result);
    response->set_success(true);

    return ::grpc::Status::OK;
}