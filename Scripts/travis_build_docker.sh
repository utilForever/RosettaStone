#!/usr/bin/env bash

set -e

if [ $# -eq 0 ]
  then
    docker build -t utilforever/hearthstonepp .
else
    docker build -f $1 -t utilforever/hearthstonepp:$2 .
fi
docker run utilforever/hearthstonepp