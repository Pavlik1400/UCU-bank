#! /bin/bash

docker build -f ./docker/services/dockerfile . --build-arg SERVICE=auth --build-arg=PRESET=release-posix -t mbilyk/auth:v1.0
docker build -f ./docker/services/dockerfile . --build-arg SERVICE=user --build-arg=PRESET=release-posix -t mbilyk/user:v1.0
docker build -f ./docker/services/dockerfile . --build-arg SERVICE=account --build-arg=PRESET=release-posix -t mbilyk/account:v1.0
docker build -f ./docker/services/dockerfile . --build-arg SERVICE=credit --build-arg=PRESET=release-posix -t mbilyk/credit:v1.0
docker build -f ./docker/services/dockerfile . --build-arg SERVICE=notification --build-arg=PRESET=release-posix -t mbilyk/notification:v1.0
docker build -f ./docker/services/dockerfile . --build-arg SERVICE=gateway --build-arg=PRESET=release-posix -t mbilyk/gateway:v1.0
docker build -f ./docker/services/dockerfile . --build-arg SERVICE=transaction --build-arg=PRESET=release-posix -t mbilyk/transaction:v1.0

# docker build -f ./docker/queue/dockerfile ./docker/queue -t mak9su4roi/queue
# docker build -f ./docker/postgres-db/dockerfile ./docker/postgres-db -t mak9su4roi/postgres-db


# docker push mbilyk/auth:v1.0
# docker push mbilyk/user:v1.0
# docker push mbilyk/account:v1.0
# docker push mbilyk/credit:v1.0
# docker push mbilyk/notification:v1.0
# docker push mbilyk/gateway:v1.0
# docker push mbilyk/transaction:v1.0
# # 
# docker push mak9su4roi/queue
# docker push mak9su4roi/postgres-db