cd ..
dir=${PWD##*/}
dir=${dir:-/}
dir=$(echo $dir | tr '[:upper:]' '[:lower:]')


docker stop $dir || true && docker rm $dir || true