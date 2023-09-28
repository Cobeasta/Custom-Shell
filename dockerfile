FROM alpine:latest as base
# Parameterize user since CLion uses host UID
# This avoids file permission issues
ARG UID=1000
RUN adduser -h /home/builder -u ${UID} -S builder -D
USER builder

FROM base as ref
USER root
# Install needed build tools
RUN apk update && apk add make gcc musl-dev
USER builder
WORKDIR /home/builder/Custom-Shell
CMD ["make"]
ENTRYPOINT /bin/sh



