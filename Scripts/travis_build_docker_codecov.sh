#!/usr/bin/env bash

set -e

ci_env=`bash <(curl -s https://codecov.io/env)`
docker build -f $1 -t utilforever/hearthstonepp:$2 .
docker run $ci_env utilforever/hearthstonepp