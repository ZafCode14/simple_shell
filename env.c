#include "shell.h"

/**
 * _setenv - sets a new variable and value for the env
 * @name: the name of the variable
 * @value: the value of the variable
 * @overwrite: overight if exitsts, when activated
 *
 * Return: 0 on success or -1 on failure
 */
int _setenv(const char *name, const char *value, int overwrite)
{
	int nameLen, valueLen, i, envCount;
	char *newEntry;
	char **newEnv;

	if (name == NULL || name[0] == '\0' || strchr(name, '=') != NULL)
		return (-1);
	nameLen = strlen(name);
	valueLen = value ? strlen(value) : 0;
	for (i = 0; environ[i]; i++)
	{
		if (strncmp(environ[i], name, nameLen) == 0 && environ[i][nameLen] == '=')
		{
			if (overwrite)
			{
				newEntry = malloc(nameLen + valueLen + 2);
				strcpy(newEntry, name);
				strcat(newEntry, "=");
				strcat(newEntry, value);
				environ[i] = newEntry;
				return (0);
			}
			return (0);
		}
	}
	newEntry = malloc(nameLen + valueLen + 2);
	strcpy(newEntry, name);
	strcat(newEntry, "=");
	strcat(newEntry, value);
	for (envCount = 0; environ[envCount] != NULL; envCount++)
		;
	newEnv = malloc((envCount + 2) * sizeof(char *));
	for (i = 0; i < envCount; i++)
		newEnv[i] = environ[i];
	newEnv[envCount] = newEntry;
	newEnv[envCount + 1] = NULL;
	environ = newEnv;
	return (0);
}
/**
 * _unsetenv - unsets a variavle and the corresponding value
 * @name: name of the variable
 *
 * Return: 0 on success or -1 on failure
 */
int _unsetenv(const char *name)
{
	int nameLen, foundIndex, i;

	if (name == NULL || name[0] == '\0' || strchr(name, '=') != NULL)
		return (-1);

	nameLen = strlen(name);
	foundIndex = -1;

	for (i = 0; environ[i] != NULL; i++)
	{
		if (strncmp(environ[i], name, nameLen) == 0 && environ[i][nameLen] == '=')
		{
			foundIndex = i;
			break;
		}
	}
	if (foundIndex == -1)
		return (0);

	free(environ[foundIndex]);

	for (i = foundIndex; environ[i] != NULL; i++)
		environ[i] = environ[i + 1];

	return (0);
}

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
