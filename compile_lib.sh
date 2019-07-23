#!/bin/bash

clear

export HOSTTYPE=Testing

make -C rendu re
make -C rendu clean

rm -f *.so
cp -r ./rendu/*.so .
rm -f ./inc/*
cp ./rendu/ft_malloc.h ./inc

if [ ! -f libft_malloc.so ]
	then
		echo "Makefile failed"
		exit
fi
