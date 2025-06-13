#include "system.hh"

#include <unistd.h>

//Helper Functions
std::string exec(const char* cmd);

::grpc::Status ProcessingImplemantation::ExecuteShell(::grpc::ServerContext* context, const ::MetaOS::ExecuteShellRequest* request, ::MetaOS::ExecuteShellResponse* response)
{
    std::string shell_prompt = request->command();
    std::vector<std::string> black_list = {"reboot", "sudo", "rm", "echo"};

    for (const auto& dangerous_cmd: black_list)
    {
        if (shell_prompt.contains(dangerous_cmd))
        {
            response->set_output("Dangerous prompt");
            response->set_success(false);

            return ::grpc::Status::OK;
        }
    }

    try {
        shell_prompt = exec(shell_prompt.c_str());

        response->set_output(shell_prompt);
        response->set_success(true);

        return ::grpc::Status::OK;

    } catch (const std::runtime_error& e) {
        std::cerr << "Error: " << e.what() << std::endl;

        response->set_output(e.what());
        response->set_success(false);

        return ::grpc::Status::OK;
    }

    return ::grpc::Status::OK;
}

std::string exec(const char* cmd) {
    std::array<char, 128> buffer;
    std::string result;
    std::unique_ptr<FILE, decltype(&pclose)> pipe(popen(cmd, "r"), pclose);
    if (!pipe) {
        throw std::runtime_error("popen() failed!");
    }
    while (fgets(buffer.data(), static_cast<int>(buffer.size()), pipe.get()) != nullptr) {
        result += buffer.data();
    }
    return result;
}