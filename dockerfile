FROM alpine:latest
# Install gRPC and its dependencies
WORKDIR /gRPC
COPY . .

RUN apk update && apk add --no-cache \
    autoconf \
    automake \
    build-base \
    cmake \
    curl \
    g++ \
    git \
    libtool \
    make \
    pkgconf \
    unzip
