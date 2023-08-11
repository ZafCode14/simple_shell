#include "shell.h"
/**
 * _strcmp - comparing two strings
 * @s1: pointer to first string
 * @s2: pointer to second string
 * Return: 0
 */
int _strcmp(char *s1, char *s2)
{
	while (*s1 != '\0' || *s2 != '\0')
	{
		if (*s1 < *s2)
			return (*s1 - *s2);
		else if (*s1 > *s2)
			return (*s1 - *s2);
		s1++;
		s2++;
	}
	return (0);
}
/**
 * _strlen - string length.
 * @s: pointer to character.
 * Return: len
 */
int _strlen(char *s)
{
	int len = 0;

	while (*s != '\0')
	{
		len++;
		s++;
	}
	return (len);
}
