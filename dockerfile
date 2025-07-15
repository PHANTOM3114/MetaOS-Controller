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
    ca-certificates && \
    pkg-config \
    && rm -rf /var/lib/apt/lists/*

COPY . /MetaOS

WORKDIR /MetaOS

RUN mkdir -p build
