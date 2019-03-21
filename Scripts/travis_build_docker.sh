#!/usr/bin/env bash

set -e

if [ $# -eq 0 ]
  then
    docker build -t utilforever/rosettastone .
else
    docker build -f $1 -t utilforever/rosettastone:$2 .
fi
docker run utilforever/rosettastone