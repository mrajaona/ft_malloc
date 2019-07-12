#!/bin/bash

clear

export HOSTTYPE=Testing

make -C rendu re
make -C rendu clean

rm -f *.so
cp -r ./rendu/*.so .
rm -f ./inc/*
cp ./rendu/ft_malloc.h ./inc

FILES=(test0 test1 test2 test3 test3.1 test4 test5 test_limit)

echo "------------ compile"

for FILE in ${FILES[@]}
do
	echo ${FILE}
	./compile_test.sh ./tests/${FILE}
done

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

for FILE in ${FILES[@]}
do
	echo ${FILE}
	./tests/${FILE}
	#/usr/bin/time -l ./tests/${FILE}
done

make fclean