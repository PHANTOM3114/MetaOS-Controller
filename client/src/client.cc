#include <iostream>
#include "client_system.hh"

int main() {
    MetaClient client(grpc::CreateChannel("localhost:50051", grpc::InsecureChannelCredentials()));

    while (true) {
        std::cout << "\n[1] Run shell script\n[0] Exit\n> ";
        int choice;
        std::cin >> choice;

        if (choice == 0) break;

        if (choice == 1) {
            std::string shell_prompt;
            std::cout << "Enter shell prompt: ";
            std::cin.ignore();
            std::getline(std::cin, shell_prompt);

            while (shell_prompt.empty()) {
                std::cout << "You dont enter anything, please try again!" << std::endl;
                std::cout << "Enter shell prompt: ";
                std::getline(std::cin, shell_prompt);
            }

            MetaOS::ExecuteShellResponse shell_response;
            client.ExecuteShellRequest(shell_prompt);
        }
        else {
            std::cout << "Invalid option.\n";
        }
    }

    return 0;
}