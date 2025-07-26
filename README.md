# MetaOS Controller  

GRPC-based Main Network Daemon of MetaOS Ecosystem, which is dedicated to gather information from all other smaller daemons

![C++](https://img.shields.io/badge/C++-20-blue.svg)
![gRPC](https://img.shields.io/badge/gRPC-v1.x-brightgreen.svg)

## Features (Planned & In-Progress)

The controller is designed to manage the following system MetaOS components via its gRPC API:

* [x] **🖥️ System Management** 
* [ ] **🔒 VPN Control**
* [ ] **⚙️ CI/CD & Developer Tooling**
* [ ] **🎬 Real-time Streaming (Experimental)**

## 🛠️ Current Technology Stack

* **Language:** C++20
* **RPC Framework:** gRPC
* **Serialization:** Protocol Buffers (Protobuf)
* **Build System:** CMake
* **Testing:** GoogleTest

*Further examples of client usage will be added here.*

## 🗺️ Roadmap

* [x] Basic remotely execute shell scripts and commands.
* [ ] Set up a fully working CI/CD pipeline with automated tests.
* [ ] Add a security layer above the shell responce and request

---
