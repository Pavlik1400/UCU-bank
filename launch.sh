#! /bin/bash

kubectl create secret generic my-secret --from-file=credentials=/home/makkusu/.aws/credentials
kubectl apply -f kube.yaml
