#include "shell.h"

/**
 * _get_shell_name - wrap-up around a staic var sh_name [SHELL_NAME]
 * @name: shell name
 *
 * Return: shell name string
 */
char *_get_shell_name(const char *name)
{
	static char sh_name[NAME_MAX];

	if (name != NULL)
		strcpy(sh_name, name);
	return (sh_name);
}
