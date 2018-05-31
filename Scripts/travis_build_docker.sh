#!/usr/bin/env bash

set -e

docker build -t utilforever/hearthstonepp .
docker run utilforever/hearthstonepp