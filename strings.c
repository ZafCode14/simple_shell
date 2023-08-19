#include "shell.h"
/**
 * _atoi - from character to integer
 * @s: pointer to string
 * Return: result
 */
int _atoi(char *s)
{
	unsigned int digit;
	unsigned int sign = 1;
	unsigned int result = 0;

	while (*s != '\0')
	{
		if (*s == '-')
			sign *= -1;
		else if (*s >= '0' && *s <= '9')
		{
			digit = *s - '0';
			result = result * 10 + digit;
		}
		else if (result > 0)
			break;
		s++;
	}
	return (sign * result);
}
/**
 * _strcat - concat two strings
 * @dest: pointer to first string
 * @src: pointer to second string
 * Return: result
 */
char *_strcat(char *dest, char *src)
{
	char *result = dest;

	while (*dest != '\0')
		dest++;
	while (*src != '\0')
	{
		*dest = *src;
		dest++;
		src++;
	}
	*dest = '\0';
	return (result);
}
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
/**
 * _strncmp - Compare at most n characters of two strings
 * @s1: First string
 * @s2: Second string
 * @n: Maximum number of characters to compare
 *
 * Return: An integer less than, equal to, or greater than zero
 * if the first n bytes of s1 are respectively less than, equal to,
 * or greater than the first n bytes of s2.
 */
int _strncmp(const char *s1, const char *s2, size_t n)
{
	while (n > 0 && *s1 && *s2 && (*s1 == *s2))
	{
		s1++;
		s2++;
		n--;
	}

	if (n == 0)
		return (0);

	return (*(unsigned char *)s1 - *(unsigned char *)s2);
}
/**
 * _strcpy - copy string
 * @dest: pointer to dest
 * @src: pointer to src
 * Return: pointer to dest
 */
char *_strcpy(char *dest, char *src)
{
	int len = 0;
	int i;

	while (src[len] != '\0')
		len++;
	len++;
	for (i = 0; i < len; i++)
	{
		dest[i] = src[i];
	}
	return (dest);
}
