cd ../docker
docker build -t clion-alpine-dev-env --build-arg=$(id -u) .
