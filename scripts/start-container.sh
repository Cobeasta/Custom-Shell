cd ..
dir=${PWD##*/}
dir=${dir:-/}
dir=$(echo $dir | tr '[:upper:]' '[:lower:]')


docker stop $dir || true && docker rm $dir || true

docker run -dit --cap-add sys_ptrace -p127.0.0.1:2222:22 -v $(pwd):/home/builder/Custom-Shell --name $dir "clion-alpine-dev-env"

scp -r makefile builder@clion_docker:~/Custom-Shell ./src
ssh builder@clion_docker -p 2222
