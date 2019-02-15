#!/bin/sh
gcc -Wall -Wextra -Werror -I./inc/ -o test main.c -lft_malloc -L. -lpthread

# include "ft_malloc.sh in main file"
