 #include "shell.h"


/**
 * _select_buildin - a function that select a buldin
 * @command: command string representation
 * Return: callback ptr if it exist or NULL
 */
int (*_select_buildin(const char *command))(state_t *)
{
	buildin_t buildins[] = {

		{"exit", _hnd_exit},
		{"env", _hnd_env},
		{"setenv", _hnd_setenv},
		{"unsetenv", _hnd_unsetenv},
		{"cd", _hnd_cd},
		{"alias", _hnd_alias},
		{NULL, NULL}
	};
	int i = 0;

	while (buildins[i].command != NULL)
	{
		if (strcmp(command, buildins[i].command) == 0)
		{
			return (buildins[i].callback);
		}
		++i;
	}
	return (NULL);
}
