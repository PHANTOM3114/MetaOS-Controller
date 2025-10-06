FROM opensuse/tumbleweed:latest
LABEL maintainer="Tux"

RUN zypper refresh && \
    zypper install -y \
    openssl \
    libopenssl-devel \
    cmake \
    gcc-c++ \
    make \
    git \
    grpc-devel \
    protobuf-devel \
    libprotobuf-c-devel \
    pkg-config \
    sudo \
    nano \
    shadow \
    && zypper clean -a

# Adding User
RUN useradd -m -s /bin/bash metauser && echo "metauser:password" | chpasswd
RUN echo "metauser ALL=(ALL) NOPASSWD:ALL" >> /etc/sudoers

# Switching to MetaUSER
USER metauser
WORKDIR /home/metauser
COPY --chown=metauser:metauser . /home/metauser/MetaOS
WORKDIR /home/metauser/MetaOS
RUN mkdir -p build