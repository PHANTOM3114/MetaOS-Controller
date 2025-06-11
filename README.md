# MetaOS Controller 🎮

![Build Status](https://img.shields.io/github/actions/workflow/status/YourUsername/YourRepo/your-workflow-file.yml?branch=main)
![License](https://img.shields.io/badge/license-MIT-blue.svg)
![C++](https://img.shields.io/badge/C++-20-blue.svg)
![gRPC](https://img.shields.io/badge/gRPC-v1.x-brightgreen.svg)

A powerful, cross-platform remote controller and system management hub, designed to be the core component of the MetaOS ecosystem. This project provides a gRPC-based API for remote procedure calls to manage and monitor a host system.

## 🌟 Core Idea & Philosophy

The goal of this project is to create a robust, secure, and efficient tool for system-level automation and remote management. It's built with performance and extensibility in mind, serving as a foundational piece for more ambitious projects.

## ✨ Features (Planned & In-Progress)

The controller is designed to manage the following system components via its gRPC API:

* **🖥️ System & Process Management:**
    * [ ] Remotely execute shell scripts and commands.
    * [ ] Manage system processes (start, stop, monitor).
    * [ ] System shutdown and reboot.
    * [ ] *[Додай сюди свої інші ідеї]*

* **🌐 Network & VPN Control:**
    * [ ] Manage system-level VPN connections (e.g., OpenVPN, WireGuard).
    * [ ] Switch between connection profiles.
    * [ ] Monitor network status.
    * *...*

* **⚙️ CI/CD & Developer Tooling:**
    * [ ] Listen for CI/CD pipeline events (via WebSockets or other means).
    * [ ] Trigger local actions based on build statuses.
    * *...*

* **🎬 Real-time Streaming (Experimental / Future):**
    * [ ] Screen/window streaming using WebRTC.
    * [ ] Remote input handling (mouse, keyboard).
    * *...*

*You can add more components you plan to control here...*

## 🛠️ Technology Stack

* **Language:** C++20
* **RPC Framework:** gRPC
* **Serialization:** Protocol Buffers (Protobuf)
* **Build System:** CMake
* **Testing:** GoogleTest

## 🚀 Getting Started

To get a local copy up and running, follow these simple steps.

### Prerequisites

You need to have the following tools and libraries installed on your system:
* CMake (version 3.20 or higher)
* A modern C++ compiler (GCC, Clang, or MSVC)
* gRPC and Protocol Buffers libraries
    * *On macOS (example): `brew install grpc protobuf`*
    * *On Ubuntu (example): `sudo apt-get install libgrpc++-dev libprotobuf-dev protobuf-compiler-grpc`*

### Building the Project

1.  **Clone the repository:**
    ```sh
    git clone [https://github.com/YourUsername/YourRepo.git](https://github.com/YourUsername/YourRepo.git)
    cd YourRepo
    ```

2.  **Configure CMake and build the project:**
    ```sh
    cmake -S . -B build -DCMAKE_BUILD_TYPE=Release
    cmake --build build --config Release
    ```

## 🏃 Usage

Once built, you can run the server and interact with it using a client.

**Run the server:**
```sh
./build/server
```

**Interact with a client (e.g., `grpcurl` for testing):**
```sh
# Example of running a shell script
grpcurl -plaintext \
        -d '{"command": "echo Hello from my controller!"}' \
        localhost:50051 \
        MetaOS.MetaControl/RunShellScriptRequest
```
*Further examples of client usage will be added here.*

## 🗺️ Roadmap

* [ ] Finalize core API for process and script management.
* [ ] Implement robust VPN management logic.
* [ ] Set up a fully working CI/CD pipeline with automated tests.
* [ ] Begin research and development for the screen streaming feature.
* See the open issues for a full list of proposed features (and known issues).

## 🤝 Contributing

Contributions, issues, and feature requests are welcome! Feel free to check the [issues page](https://github.com/YourUsername/YourRepo/issues).

## 📄 License

This project is licensed under the MIT License - see the `LICENSE.md` file for details.

---
