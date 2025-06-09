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
            std::string cmd;
            std::cout << "Enter shell command: ";
            std::cin.ignore();
            std::getline(std::cin, cmd);

            MetaOS::Response res = client.RunShellScript(cmd);
            std::cout << "Output: " << res.output() << "\nSuccess: " << std::boolalpha << res.success() << "\n";
        } else {
            std::cout << "Invalid option.\n";
        }
    }

    return 0;
}