FROM ubuntu:18.10
LABEL maintainer "Chris Ohk <utilforever@gmail.com>"

RUN apt-get update && apt-get install -y \
    build-essential \
    python-dev \
    python-pip \
    python3-dev \
    python3-pip \
    python3-venv \
    python3-setuptools \
    cmake \
    --no-install-recommends \
    && rm -rf /var/lib/apt/lists/*

COPY . /app

WORKDIR /app/build
RUN cmake .. && \
    make -j "$(nproc)" && \
    make install && \
    bin/UnitTests

WORKDIR /app/ENV3
RUN pip3 install -r ../requirements.txt && \
    pip3 install .. && \
    python3 -m pytest ../Tests/PythonTests/

WORKDIR /