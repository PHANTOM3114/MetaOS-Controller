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
            std::cout << "Enter shell command: ";
            std::cin.ignore();
            std::getline(std::cin, shell_prompt);

            MetaOS::ExecuteShellResponse shell_response;
            client.ExecuteShellRequest(shell_prompt, &shell_response);
            std::cout << "Output: " << shell_response.output() << "\n";
        }
        else {
            std::cout << "Invalid option.\n";
        }
    }

    return 0;
}