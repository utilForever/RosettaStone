FROM ubuntu:18.04
LABEL maintainer="Chris Ohk <utilforever@gmail.com>"

RUN apt-get update -yq && \
    apt-get install -yq --no-install-recommends build-essential python-dev python-pip python3-dev python3-pip python3-venv cmake lcov && \
    apt-get clean && \
    rm -rf /var/lib/apt/lists/*

COPY . /app

WORKDIR /app/build
RUN cmake .. && \
    make -j "$(nproc)" && \
    make install && \
    bin/UnitTests
