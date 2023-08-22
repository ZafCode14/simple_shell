#include "shell.h"

/**
 * _strrev - reverce the str
 * @str: string
 * Return: str, but now it is rev
 */
char *_strrev(char *str)
{
	int size = 0;
	int i = 0;

	if (str == NULL)
		return (NULL);

	size = strlen(str);

	while (i < size / 2)
	{
		char tmp = str[i];

		str[i] = str[size - 1 - i];
		str[size - 1 - i] = tmp;
		++i;
	}
	return (str);

}
