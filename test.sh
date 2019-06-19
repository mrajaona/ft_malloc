#!/bin/bash

clear

rm ./lib/*
cp -R ./rendu/lib/* ./lib
rm ./inc/*
cp ./rendu/ft_malloc.h ./inc

echo

echo -n "./lib "
ls -l ./lib
echo -n ">> file: " && file -L ./lib/libft_malloc.so

echo

# gcc -Wall -Wextra -Werror -I./inc/ -L./lib -lft_malloc -o test main.c
gcc -Wall -Wextra -Werror -I./inc/ -L./lib -lft_malloc_x86_64_Darwin -o test main.c

echo

# export DYLD_LIBRARY_PATH="./lib"
# export DYLD_INSERT_LIBRARIES="libft_malloc.so"
# export DYLD_FORCE_FLAT_NAMESPACE=1

echo "------------"

./test