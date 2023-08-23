#include "shell.h"

void _sigint_hnd(int sig);

/**
 * main - SHELL program
 * @argc: args count
 * @argv: args vector
 *
 * Return: 0
 */
int main(int argc, char *argv[])
{
	state_t state;

	signal(SIGINT, _sigint_hnd);

	_init_state(&state);
	state.shell_argv = argv;
	_get_shell_name(argv[0]);
	if (argc == 1)
	{
		state.fd_input = STDIN_FILENO;
	}
	else if (argc == 2)
	{
		state.fd_input  = open(argv[1], O_RDONLY);
		if (state.fd_input == -1)
		{
			_free_state(&state);
			_print_string(STDERR_FILENO, SHELL_NAME);
			_print_string(STDERR_FILENO, ": 0: ");
			_print_string(STDERR_FILENO, ECANTOPEN_STRING);
			_print_string(STDERR_FILENO, argv[1]);
			_print_string(STDERR_FILENO, "\n");
			exit(ENFOUND);
		}
	}
	_lanch_shell(&state);
	return (0);
}
/**
 * _sigint_hnd - call back to skip ctrl-c
 * @sig: signal
 */
void _sigint_hnd(int sig)
{
	(void)sig;
	write(STDOUT_FILENO, "\n", 1);
	_print_cursor();
}
