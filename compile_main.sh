#!/bin/sh

rm test
gcc -Wall -Wextra -Werror -I. -o test main.c -lpthread -L. -lft_malloc

