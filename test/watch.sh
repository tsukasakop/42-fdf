#!/bin/bash

set -e

while true
do
    make > /dev/null
    ./fdf &
    sleep 5
    kill $!
done
