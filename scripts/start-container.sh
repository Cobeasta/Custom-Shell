SCRIPT_DIR=$( cd -- "$( dirname -- "${BASH_SOURCE[0]}" )" &> /dev/null && pwd )

cd $SCRIPT_DIR/..  || exit
pardir=${PWD##*/}
pardir=${pardir:-/}
name=$(echo $pardir | tr '[:upper:]' '[:lower:]')


docker stop $name || true && docker rm $name || true

docker run -dit --cap-add sys_ptrace -p127.0.0.1:2222:22 -v //$(pwd)\://'/home/builder/'"$pardir" --name $name "clion-alpine-dev-env"

scp -r makefile ./src builder@clion_docker:~/$pardir
ssh builder@clion_docker -p 2222