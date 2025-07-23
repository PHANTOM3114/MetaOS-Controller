#include <iostream>
#include "client_system.hh"

// using MetaOS::EchoService;
// using MetaOS::EchoRequest;
// using MetaOS::EchoResponse;
//
// class EchoClient {
// public:
//     // Конструктор: створюємо stub (об'єкт для виклику RPC)
//     EchoClient(std::shared_ptr<grpc::Channel> channel)
//         : stub_(EchoService::NewStub(channel)) {}
//
//     void Run() {
//         grpc::ClientContext context;
//
//         // Створюємо асинхронний стрім
//         auto stream = stub_->DoEcho(&context);
//
//         // Запускаємо окремий потік, який буде тільки читати відповіді від сервера
//         std::thread reader_thread([&stream]() {
//             EchoResponse response;
//             while (stream->Read(&response)) {
//                 std::cout << "CLIENT RECEIVED: " << response.message() << std::endl;
//             }
//         });
//
//         // В основному потоці відправляємо кілька повідомлень на сервер
//         for (int i = 0; i < 5; ++i) {
//             EchoRequest request;
//             std::string message = "ping " + std::to_string(i);
//             request.set_message(message);
//
//             std::cout << "CLIENT SENDING: " << message << std::endl;
//             if (!stream->Write(request)) {
//                 // Помилка запису, стрім обірвався
//                 break;
//             }
//             std::this_thread::sleep_for(std::chrono::seconds(1));
//         }
//
//         // Повідомляємо серверу, що ми закінчили відправляти повідомлення
//         stream->WritesDone();
//
//         // Чекаємо, поки потік читання завершиться
//         reader_thread.join();
//
//         // Отримуємо фінальний статус RPC
//         grpc::Status status = stream->Finish();
//         if (status.ok()) {
//             std::cout << "RPC finished successfully." << std::endl;
//         } else {
//             std::cout << "RPC failed with error: " << status.error_message() << std::endl;
//         }
//     }
//
// private:
//     std::unique_ptr<EchoService::Stub> stub_;
// };

// int main() {
//     MetaClient client(grpc::CreateChannel("metaos-server:50051", grpc::InsecureChannelCredentials()));
//
//     client.ExecuteShellRequest();
//     // std::string server_address("metaos-server:50051");
//     //
//     // // Створюємо клієнта
//     // EchoClient client(grpc::CreateChannel(server_address, grpc::InsecureChannelCredentials()));
//     //
//     // // Запускаємо його
//     // std::cout << "Client started. Will send 5 pings." << std::endl;
//     // client.Run();
//
//     return 0;
// }

// ВАЖЛИВО: Заміни MetaOS:: на твій неймспейс
using grpc::Channel;
using grpc::ClientContext;
using grpc::Status;
using MetaOS::ShellControllerService;
using MetaOS::ExecuteShellRequest;
using MetaOS::ExecuteShellResponse;

class ShellClient {
public:
    ShellClient(std::shared_ptr<Channel> channel)
        : stub_(ShellControllerService::NewStub(channel)) {}

    void ExecuteCommand(const std::string& command) {
        ClientContext context;

        std::unique_ptr<grpc::ClientReaderWriter<ExecuteShellRequest, ExecuteShellResponse>> stream(
            stub_->ExecuteShell(&context));

        std::thread reader_thread([&stream]() {
            ExecuteShellResponse response;
            // Цикл читання: виводимо все, що приходить від сервера, поки стрім живий
            while (stream->Read(&response)) {
                std::cout << response.output(); // ДРУКУЄМО ВИВІД ВІД СЕРВЕРА
            }
        });

        ExecuteShellRequest request;
        request.set_command(command);
        std::cout << "--> Sending command: " << command << "\n";
        stream->Write(request);

        stream->WritesDone();

        reader_thread.join();

        Status status = stream->Finish();
        if (!status.ok()) {
            std::cout << "\nRPC failed: " << status.error_message() << std::endl;
        }
    }

private:
    std::unique_ptr<ShellControllerService::Stub> stub_;
};

int main(int argc, char** argv) {
    std::string server_address("metaos-server:50051");
    ShellClient client(grpc::CreateChannel(server_address, grpc::InsecureChannelCredentials()));

    std::cout << "Enter shell command (e.g., 'ls -la') or type 'exit' to quit." << std::endl;

    for (std::string command; std::cout << "> " && std::getline(std::cin, command) && command != "exit";) {
        if (command.empty()) continue;
        client.ExecuteCommand(command);
    }

    std::cout << "Exiting." << std::endl;

    return 0;
}