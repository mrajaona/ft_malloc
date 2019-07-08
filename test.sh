#!/bin/bash

clear

export HOSTTYPE=Testing

make -C rendu re
make -C rendu clean

rm -f *.so
cp -r ./rendu/*.so .
rm -f ./inc/*
cp ./rendu/ft_malloc.h ./inc

echo "------------ compile"

rm test
gcc -Wall -Wextra -Werror -I./inc/ -o test main.c -lpthread -L. -lft_malloc

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

if [ -f ./test ]
	then
	/usr/bin/time -l ./test
fi
