#include "shell.h"
/**
 * _exec - a wrap-up around execve syscall
 * @state: a shell state represent the current state of the shell
 * Return: 0 on on success or -1
 */
int _exec(state_t *state)
{
	char *path = NULL;
	pid_t child = -1;
	int status = 0;
	int (*buildin_callback)(state_t *) = NULL;

	buildin_callback = _select_buildin(state->args[0]);
	if (buildin_callback)
	{
		state->last_cmd_status = buildin_callback(state);
		return (0);
	}
	if (!_is_path(state->args[0]))
	{
		path = _program_path(state->args[0], state->env_head);
		if (!path)
		{
			state->last_cmd_status = ENFOUND;
			_print_string(STDERR_FILENO, SHELL_NAME);
			_print_string(STDERR_FILENO, ": 1: ");
			_print_string(STDERR_FILENO, state->args[0]);
			_print_string(STDERR_FILENO, ENFOUND_STRING);
			return (0);
		}
	}
	else
		path = strdup(state->args[0]);
	child = fork();
	if (child < 0)
		return (-1);
	if (child == 0) /* child process */
	{
		execve(path, state->args, *(state->environ));
		/* is execve returned that means that ther is an error */
		state->last_cmd_status = errno;
		return (0);
	}
	if (wait(&status) > 0 && WIFEXITED(status))
		state->last_cmd_status = WEXITSTATUS(status);
	free(path);
	return (0);
}
