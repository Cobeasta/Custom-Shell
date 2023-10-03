#!/bin/bash

SCRIPT_DIR=$( cd -- "$( dirname -- "${BASH_SOURCE[0]}" )" &> /dev/null && pwd )

cd $SCRIPT_DIR  || exit
cd ..
pardir=${PWD##*/}
pardir=${pardir:-/}
name=$(echo $pardir | tr '[:upper:]' '[:lower:]')



COMPOSE_PROJECT_NAME="$pardir" docker compose up -d

ssh builder@clion_docker -p 2222 && docker compose down


#docker stop $name || true && docker rm $name || true

#docker run -dit --cap-add sys_ptrace -p127.0.0.1:2222:22\
#  --mount type=bind,source=//$(pwd)//makefile  //'/home/builder/'"$pardir"  --name $name "clion-alpine-dev-env"

