FROM ubuntu:22.04

LABEL Description="Build environment"

ENV HOME /root
ENV DEBIAN_FRONTEND=noninteractive

SHELL ["/bin/bash", "-c"]

RUN apt-get update && apt-get -y --no-install-recommends install \
    build-essential \
    clang \
    cmake \
    gdb \
    git \
    gcc \
    g++ \
    libjsoncpp-dev \
    uuid-dev \
    zlib1g-dev \
    postgresql-all \
    make \
    curl \
    wget


WORKDIR /opt
RUN apt-get install --reinstall ca-certificates
# RUN git clone https://github.com/drogonframework/drogon

ADD ext/drogon /opt/drogon
WORKDIR /opt/drogon
RUN git submodule update --init

WORKDIR /opt/drogon/build
RUN cmake ..
RUN make install
RUN make

RUN mkdir /opt || true
RUN mkdir /opt/server

RUN mkdir /opt/server/src
RUN mkdir /opt/server/src/modules


ADD src /opt/server

ADD CMakeLists.txt /opt/server
ADD config.json /opt/server
ADD config.yaml /opt/server
ADD main.cc /opt/server
ADD src/modules/unicodeConvertor.h /opt/server/src/modules
ADD src/modules/unicodeConvertor.cc /opt/server/src/modules
ADD models /opt/server/models
ADD controllers /opt/server/controllers
ADD libs /opt/server/libs

#RUN mkdir /opt/server/build

WORKDIR /opt/server

#RUN drogon_ctl create model models -y || true

WORKDIR /opt/server/build

RUN cmake ..
RUN make

ADD server-run.sh /opt/server/build
RUN chmod +x /opt/server/build/server-run.sh

ENTRYPOINT ["./server-run.sh"]
#CMD tail -f /dev/null