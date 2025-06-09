#include "system.hh"

#include <unistd.h>

::grpc::Status ProcessingImplemantation::ShutdownSystemRequest(::grpc::ServerContext* context, const ::MetaOS::ShutdownSystem& request, ::MetaOS::Response* response)
{
    bool result = std::system("echo ShutdownSystemRequest");
    response->set_output("ShutdownSystemRequest");
    response->set_success(result == 0);
    return ::grpc::Status::OK;
}

::grpc::Status ProcessingImplemantation::RunShellScriptRequest(::grpc::ServerContext* context, const ::MetaOS::RunShellScript& request, ::MetaOS::Response* response)
{
    bool result;
    std::string method = "RunShellScriptRequest";
    
    #if defined(_WIN32) || defined(_WIN64)
        result = std::system("echo RunShellScriptRequest");
    #elif defined(__APPLE__)
        result = std::system("echo RunShellScriptRequest");
    #elif defined(__linux__)
        result = std::system("echo RunShellScriptRequest");
    #else
        result = false;
        std::cerr << "Unsupported OS";
    #endif
    
    response->set_output(method);
    response->set_success(result == 0);
    
    return ::grpc::Status::OK;
}

::grpc::Status ProcessingImplemantation::OpenAppRequest(::grpc::ServerContext* context, const ::MetaOS::OpenApp& request, ::MetaOS::Response* response)
{
    bool result;
    std::string method = "RunShellScriptRequest";

    #if defined(_WIN32) || defined(_WIN64)
    #elif defined(__APPLE__)
    // Showing the list of applications
        pid_t openApp = fork();

        if (openApp == -1) {
            perror("fork");
            exit(EXIT_FAILURE);
        }
        else if (openApp == 0) {
            execlp("ls", "ls", "/Applications", (char*)nullptr);

            perror("execlp");
            exit(EXIT_FAILURE);
        }
        else {
            wait(nullptr);
        }

    // Opening the application

    #elif defined(__linux__)
    #else
        result = false;
        std::cerr << "Unsupported OS";
    #endif

    response->set_output("OpenAppRequest");
    response->set_success(result == 0);
    return ::grpc::Status::OK;
}
