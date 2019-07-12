#!/bin/sh

rm $1
gcc -Wall -Wextra -Werror -I./inc -o $1 $1.c -lpthread -L. -lft_malloc
