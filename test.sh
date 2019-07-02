#!/bin/bash

clear

make -C rendu re
make -C rendu clean

rm -f *.so
cp ./rendu/*.so .
rm -f ./inc/*
cp ./rendu/ft_malloc.h ./inc

gcc -Wall -Wextra -Werror -I./inc/ -L. -lft_malloc -o test main.c

if [ $# -eq 0 ]

	then
	echo "------------ system"

elif [ $1 = "macos" ]

	then
	echo "------------ macos"

	export DYLD_LIBRARY_PATH=.
	export DYLD_INSERT_LIBRARIES="libft_malloc.so"
	export DYLD_FORCE_FLAT_NAMESPACE=1

elif [ $1 = "linux" ]

	then
	echo "------------ linux"

	export LD_LIBRARY_PATH=.
	export LD_PRELOAD="libft_malloc.so"

fi

./test
