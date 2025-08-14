# MetaOS Controller  

GRPC-based Main Network Daemon of MetaOS Ecosystem, which is dedicated to gather information from all other smaller daemons

![C++](https://img.shields.io/badge/C++-20-blue.svg)
![gRPC](https://img.shields.io/badge/gRPC-v1.x-brightgreen.svg)

## 🏛️ Architecture

The system is built on the interaction of two key components:

* **Controllers:** Logical units within `MetaOS-Controller` responsible for a specific functional area which will communicate with modules.
* **Modules:** Separate, independent applications that perform this functions. 

## 🕹️ Core Controllers & Modules

* [x] **🐚 Shell Controller:** Provides secure access to the system shell and command execution. *[Status: MVP Ready]*
* [ ] **🚀 CI/CD Controller:** Enables monitoring and management of pipelines (initial target: GitHub Actions). *[Status: In Progress]*
* [ ] **☁️ Cloud Controller:** Integration with cloud services and providers for remote access. *[Status: Planned]*
* [ ] **🛡️ VPN Controller:** Manages VPN connections based on predefined scenarios (e.g., when connecting to a public network). *[Status: Planned]*
* [ ] **🧠 AI Controller:** Integration with LLMs for user assistance and learning. *[Status: Planned]*


## 🛠️ Current Technology Stack

* **Language:** C++23
* **RPC Framework:** gRPC
* **Serialization:** Protocol Buffers (Protobuf)
* **Build System:** CMake
* **Testing:** GoogleTest
* **Key Libraries:** Boost.asio

## 🗺️ Roadmap

* [x] **Q3 2025:** Completed the `Shell Controller` MVP (basic command execution via `forkpty` and `epoll`).
* [ ] **Q4 2025:** Develop the `CI/CD Controller` MVP and a dashboard module for GitHub Actions.

---
