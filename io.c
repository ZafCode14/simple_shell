#include "shell.h"


/**
 * _print_string - prints a string
 * @fd: file descriptor
 * @str: string
 * Return: -1 or the number of char printed
 */
ssize_t _print_string(int fd, const char *str)
{
	return (write(fd, str, strlen(str)));
}

/**
 * _print_number - prints a int
 * @fd: file descriptor
 * @i: the number
 * Return: -1 or the number of char printed
 */
ssize_t _print_number(int fd, long int i)
{
	char *str = int_to_str(i);

	ssize_t r = _print_string(fd, str);

	free(str);

	return (r);
}
