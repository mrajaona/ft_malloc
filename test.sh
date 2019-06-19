#!/bin/bash

clear

rm -f *.so
cp ./rendu/*.so .
rm -f ./inc/*
cp ./rendu/ft_malloc.h ./inc

gcc -Wall -Wextra -Werror -I./inc/ -L. -lft_malloc -o test main.c

echo "------------ system"

./test

echo "------------ custom"

export DYLD_LIBRARY_PATH=.
export DYLD_INSERT_LIBRARIES="libft_malloc.so"
export DYLD_FORCE_FLAT_NAMESPACE=1

./test
