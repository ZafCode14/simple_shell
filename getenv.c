#include "shell.h"

/**
 * _getenv - getting environment
 * @name: pointer the name of the env
 *
 * Return: NULL
 */
char *_getenv(const char *name)
{
	size_t name_length = _strlen((char *)name);
	int i;

	for (i = 0; environ[i] != NULL; i++)
		if (_strncmp(name, environ[i], name_length) == 0 &&
		environ[i][name_length] == '=')
			return (environ[i] + name_length + 1);

	return (NULL);
}
