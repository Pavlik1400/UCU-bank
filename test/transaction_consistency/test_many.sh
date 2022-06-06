#!/usr/bin/env bash

python3 test.py --N 1000 --n 0 &
python3 test.py --N 1000 --n 1 &
python3 test.py --N 1000 --n 2 &
python3 test.py --N 1000 --n 3
