#include "shell.h"

/**
 * _digits - calculate base 10 digit count
 * @i: the int value
 * Return: digit count
 */
int _digits(long int i)
{
	int r = 1;

	if (i / 10 != 0)
		r +=  _digits(i / 10);
	return (r);
}

/**
 * int_to_str - returns the string representation of long int
 * @i: the int value
 * Return: the string or NULL on failure
 */
char *int_to_str(long int i)
{
	char *str = NULL;
	int index = 0;
	int size = 0;
	int negative = 0;

	if (i >= 0)
		i = -i;
	else
		negative = 1;
	size = _digits(i);
	if (negative)
		str = malloc(sizeof(char) * (size + 2));
	else
		str = malloc(sizeof(char) * (size + 1));

	if (!str)
		return (NULL);
	while (index < size)
	{
		str[index] = '0' - (int)(i % 10);
		i = i / 10;
		++index;
	}
	if (negative)
	{
		str[index] = '-';
		++index;
	}
	str[index] = '\0';

	str = _strrev(str);
	return (str);
}
