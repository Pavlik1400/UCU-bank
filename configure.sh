#!/usr/bin/env bash

mkdir -p dependecies
cd dependecies
if [ ! -e drogon ]
then
  git clone https://github.com/drogonframework/drogon
  cd drogon
  git submodule update --init
else
    echo "drogon is already installed - skipping"
fi




