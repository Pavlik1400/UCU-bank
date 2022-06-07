#! /bin/bash

docker build -f ./docker/services/dockerfile . --build-arg SERVICE=auth --build-arg=PRESET=release-posix -t mak9su4roi/auth:v2 
docker push mak9su4roi/auth:v2

docker build -f ./docker/services/dockerfile . --build-arg SERVICE=user --build-arg=PRESET=release-posix -t mak9su4roi/user:v2
docker push mak9su4roi/user:v2

docker build -f ./docker/services/dockerfile . --build-arg SERVICE=account --build-arg=PRESET=release-posix -t mak9su4roi/account:v2
docker push mak9su4roi/account:v2

docker build -f ./docker/services/dockerfile . --build-arg SERVICE=credit --build-arg=PRESET=release-posix -t mak9su4roi/credit:v2
docker push mak9su4roi/credit:v2

docker build -f ./docker/services/dockerfile . --build-arg SERVICE=notification --build-arg=PRESET=release-posix -t mak9su4roi/notification:v2
docker push mak9su4roi/notification:v2

docker build -f ./docker/services/dockerfile . --build-arg SERVICE=gateway --build-arg=PRESET=release-posix -t mak9su4roi/gateway:v2
docker push mak9su4roi/gateway:v2

docker build -f ./docker/services/dockerfile . --build-arg SERVICE=transaction --build-arg=PRESET=release-posix -t mak9su4roi/transaction:v2
docker push mak9su4roi/transaction:v2

docker build -f ./docker/queue/dockerfile ./docker/queue -t mak9su4roi/queue
docker push mak9su4roi/queue

docker build -f ./docker/postgres-db/dockerfile ./docker/postgres-db -t mak9su4roi/postgres-db
docker push mak9su4roi/postgres-db