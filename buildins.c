#include "shell.h"

/**
 * _hnd_exit - handle the exit buildin
 * @state: shell state
 * Return: 0 on success
 */
int _hnd_exit(state_t *state)
{
	state->running = 0;
	if (state->args[1])
	{
		if (strlen(state->args[1]) == strspn(state->args[1], "0123456789"))
			state->last_cmd_status = atoi(state->args[1]);
		else
		{
			_print_string(STDERR_FILENO, SHELL_NAME);
			_print_string(STDERR_FILENO, ": 1: ");
			_print_string(STDERR_FILENO, state->args[0]);
			_print_string(STDERR_FILENO, EILLEGALE_STRING);
			_print_string(STDERR_FILENO, state->args[1]);
			_print_string(STDERR_FILENO, "\n");
			state->last_cmd_status = EILLEGALE;
		}

	}
	return (state->last_cmd_status);
}
/**
 * _hnd_env - [cpy] printf the striron variable
 * @state: shell state
 * Return: 0 on success
 */
int _hnd_env(state_t *state)
{
	entry_node_t *node  = state->env_head;

	if (node == NULL)
	{
		return (-1);
	}
	while (node)
	{
		printf("%s=", node->key);
		if (node->value)
			printf("%s", node->value);
		printf("\n");
		node = node->next;
	}
	return (0);
}

/**
 * _hnd_setenv - callback that handle setenv
 * @state: shell state
 * Return: 0 on success
 */
int _hnd_setenv(state_t *state)
{
	if (state->args[1] == NULL || state->args[2] == NULL)
	{
		return (-1);
	}
	if (_push_entry_node(&(state->env_head), state->args[1], state->args[2]) < 0)
	{
		perror(SHELL_NAME);
		return (-1);
	}
	_free_env_table(*(state->environ));
	*(state->environ) = _construct_env_table(state->env_head);
	return (0);
}

/**
 * _hnd_unsetenv - callback that handle unsetenv
 * @state: shell state
 * Return: 0 on success
 */
int _hnd_unsetenv(state_t *state)
{
	if (state->args[1] == NULL)
	{
		char *str = "Usage: unsetstr key\n";

		write(STDERR_FILENO, str, strlen(str));
		return (-1);
	}
	if (_delete_entry_node(&(state->env_head), state->args[1]) < 0)
	{
		perror(SHELL_NAME);
		return (-1);
	}
	_free_env_table(*(state->environ));
	*(state->environ) = _construct_env_table(state->env_head);
	return (0);
}
