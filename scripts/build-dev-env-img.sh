#!/bin/bash
SCRIPT_DIR=$( cd -- "$( dirname -- "${BASH_SOURCE[0]}" )" &> /dev/null && pwd )
cd $SCRIPT_DIR || exit

cd ../docker
docker build -t clion-alpine-dev-env --build-arg=$(id -u) .