# MetaOS Controller 

!!!WARNING!!!

This project is experemental which now developing for education only

![C++](https://img.shields.io/badge/C++-20-blue.svg)
![gRPC](https://img.shields.io/badge/gRPC-v1.x-brightgreen.svg)

## Features (Planned & In-Progress)

The controller is designed to manage the following system components via its gRPC API:

* **🖥️ System & Process Management:**
    * [+] Basic remotely execute shell scripts and commands.
    * [ ] Manage system processes (start, stop, monitor).

* **🌐 Network & VPN Control:**
    * [ ] Manage system-level VPN connections (e.g., OpenVPN, WireGuard).
    * [ ] Switch between connection profiles.
    * [ ] Monitor network status.

* **⚙️ CI/CD & Developer Tooling:**
    * [ ] Listen for CI/CD pipeline events (via WebSockets or other means).
    * [ ] Trigger local actions based on build statuses.

* **🎬 Real-time Streaming (Experimental / Future):**
    * [ ] Screen/window streaming using WebRTC.
    * [ ] Remote input handling (mouse, keyboard).

## 🛠️ Current Technology Stack

* **Language:** C++20
* **RPC Framework:** gRPC
* **Serialization:** Protocol Buffers (Protobuf)
* **Build System:** CMake
* **Testing:** GoogleTest

*Further examples of client usage will be added here.*

## 🗺️ Roadmap

* [+] Make a stream-output of shell responce
* [ ] Add a security layer above the shell responce and request
* [ ] Set up a fully working CI/CD pipeline with automated tests.

---
