FROM ubuntu:latest

RUN apt-get update && apt-get install -y \
    cmake \
    g++ \
    build-essential \
    git \
    libgrpc++-dev \
    libgrpc-dev \
    protobuf-compiler-grpc \
    libprotobuf-dev \
    pkg-config \
    sudo \
    && rm -rf /var/lib/apt/lists/*

RUN useradd -m -s /bin/bash metauser && echo "metauser:password" | chpasswd

RUN adduser metauser sudo

USER metauser
WORKDIR /home/metauser

COPY . /MetaOS

WORKDIR /MetaOS

RUN mkdir -p build
