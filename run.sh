#!/bin/sh
gcc -Wall -Werror -Wextra -pedantic -std=gnu89 *.c -D DEBUG -g -o hsh && valgrind --track-origins=yes --leak-check=full --show-leak-kinds=all ./hsh
