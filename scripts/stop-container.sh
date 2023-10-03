#!/bin/bash
SCRIPT_DIR=$( cd -- "$( dirname -- "${BASH_SOURCE[0]}" )" &> /dev/null && pwd )
cd $SCRIPT_DIR/.. || exit
dir=${PWD##*/}
dir=${dir:-/}
dir=$(echo $dir | tr '[:upper:]' '[:lower:]')

docker stop $dir || true && docker rm $dir || true