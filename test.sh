#!/bin/sh

clear

export HOSTTYPE=Testing

make re
make clean

./compile_main.sh
./run.sh $@
