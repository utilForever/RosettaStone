FROM ubuntu:18.04
MAINTAINER Chris Ohk <utilForever@gmail.com>

RUN apt-get update -yq && \
    apt-get install -yq --no-install-recommends libxrandr-dev libxi-dev libxxf86vm-dev libxinerama-dev libxcursor-dev xorg-dev libglu1-mesa-dev lcov && \
    apt-get install -yq build-essential cmake wget unzip;

RUN wget https://github.com/glfw/glfw/releases/download/3.2.1/glfw-3.2.1.zip;
RUN unzip glfw-3.2.1.zip && \
    cd glfw-3.2.1 && \
    cmake -DBUILD_SHARED_LIBS=true -DGLFW_BUILD_EXAMPLES=false -DGLFW_BUILD_TESTS=false -DGLFW_BUILD_DOCS=false . && \
    make -j $CPU_NUM install && \
    cd ..;

ADD . /app

WORKDIR /app/build
RUN cmake .. && \
    make -j`nproc` && \
    make install

WORKDIR /
