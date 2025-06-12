# MetaOS Controller 🎮

![Build Status](https://img.shields.io/github/actions/workflow/status/YourUsername/YourRepo/your-workflow-file.yml?branch=main)
![License](https://img.shields.io/badge/license-MIT-blue.svg)
![C++](https://img.shields.io/badge/C++-20-blue.svg)
![gRPC](https://img.shields.io/badge/gRPC-v1.x-brightgreen.svg)

A powerful, cross-platform remote controller and system management hub, designed to be the core component of the MetaOS ecosystem. This project provides a gRPC-based API for remote procedure calls to manage and monitor a host system.

## 🌟 Core Idea & Philosophy

This controller is a part of the much more bigger project - MetaOS. Controller has a set of features for controlling your linux pc remotely, its not an Anydesk, but more specific.

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

*Further examples of client usage will be added here.*

## 🗺️ Roadmap

* [ ] Finalize core API for process and script management.
* [ ] Implement robust VPN management logic.
* [ ] Set up a fully working CI/CD pipeline with automated tests.
* [ ] Begin research and development for the screen streaming feature.
* See the open issues for a full list of proposed features (and known issues).


---
