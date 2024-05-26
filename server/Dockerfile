FROM ubuntu:22.04

LABEL Description="Build environment"

ENV HOME /root

SHELL ["/bin/bash", "-c"]

RUN apt-get update && apt-get -y --no-install-recommends install \
    build-essential \
    clang \
    cmake \
    gdb \
    wget

RUN mkdir /opt || true
RUN mkdir /opt/server
ADD build /opt/server
ADD controllers /opt/server
ADD libs /opt/server
ADD src /opt/server
ADD CMakeLists.txt /opt/server
ADD config.json /opt/server
ADD config.yaml /opt/server
ADD main.cc /opt/server

WORKDIR /opt/server/

RUN <<EOF
ls
cmake ..
make
EOF