#include "shell.h"

/**
 * _hnd_cd - callback that handle cd
 * @state: shell state
 * Description: [info]make a deep cpy needed for the swap of [cd -]
 * Return: 0 on success
 */
int _hnd_cd(state_t *state)
{
	char *path = NULL;
	const char *prev_pwd = NULL;

	if (state->args[1] == NULL)
	{
		if (_get_value(state->env_head, "HOME"))
			path = strdup(_get_value(state->env_head, "HOME"));
	}
	else if (strcmp(state->args[1], "-") == 0)
	{
		if (_get_value(state->env_head, "OLDPWD"))
			path = strdup(_get_value(state->env_head, "OLDPWD"));
		else
			path = strdup(_get_value(state->env_head, "PWD"));
	}
	else
		path = strdup(state->args[1]);
	if (path)
	{
		if (chdir(path) < 0)
		{
			_print_string(STDERR_FILENO, SHELL_NAME);
			_print_string(STDERR_FILENO, ": 1: ");
			_print_string(STDERR_FILENO, ECANTCD_STRING);
			_print_string(STDERR_FILENO, path);
			_print_string(STDERR_FILENO, "\n");
			return (0);
		}
		if (state->args[1] && strcmp(state->args[1], "-") == 0)
		{
			_print_string(STDOUT_FILENO, path);
			_print_string(STDOUT_FILENO, "\n");
		}
		prev_pwd = _get_value(state->env_head, "PWD");
		_push_entry_node(&(state->env_head), "OLDPWD", prev_pwd);
		_push_entry_node(&(state->env_head), "PWD", path);
		_free_env_table(*(state->environ));
		*(state->environ) = _construct_env_table(state->env_head);
	}
	free(path);
	return (0);
}
