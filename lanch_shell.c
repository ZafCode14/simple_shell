#include "shell.h"
/**
 * _lanch_shell - the core function of the shell program
 * @state: state of the shell ptr
 * Descripion: reading from fd_input, witch may be the STDIN linked to the tty
 * or pipe or a file a script
 */
void _lanch_shell(state_t *state)
{
	char *input = NULL;
	size_t size = 0;

	while (1)
	{
		if (isatty(state->fd_input))
			_print_cursor();
		input = NULL;
		size = 0;
		if (_getline(&input, &size, state->fd_input) <= 0)
		{
			free(input);
			_free_state(state);
			exit(state->last_cmd_status);
		}
#ifdef DEBUG
		printf("[input] %ld, %s\n", strlen(input), input);
#endif
		input[strlen(input) - 1] = '\0';
#ifdef DEBUG
		printf("[input] %ld, %s\n", strlen(input), input);
#endif
		_cut_comments(input);

		if (_handle_command(input, state) < 0)
		{
			perror(SHELL_NAME);
			free(input);
			_free_state(state);
			exit(-1);
		}
		free(input);
		if (!state->running)
		{
			_free_state(state);
			exit(state->last_cmd_status);
		}
	}
}
