#! /bin/bash

kubectl create secret generic my-secret --from-file=credentials=credentials
kubectl apply -f kube.yaml
