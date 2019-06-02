FROM ubuntu:19.04
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
    gcc-8 \
    g++-8 \
    --no-install-recommends \
    && rm -rf /var/lib/apt/lists/*

COPY . /app

WORKDIR /app/build
RUN cmake .. -DCMAKE_C_COMPILER=gcc-8 -DCMAKE_CXX_COMPILER=g++-8 && \
    make -j "$(nproc)" && \
    make install && \
    bin/UnitTests

WORKDIR /app/ENV3
RUN pip3 install -r ../requirements.txt && \
    pip3 install .. && \
    python3 -m pytest ../Tests/PythonTests/
    
WORKDIR /