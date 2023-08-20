#include "shell.h"

/**
 * main - entry point
 *
 * Return: 0
 */
int main(void)
{
	int interactive = isatty(STDIN_FILENO);

	dir_h = NULL;
	linked_dirs("PATH");
	if (interactive)
		handle_interactive_mode();
	else
		handle_non_interactive_mode();
	free_dirs();

	return (0);
}

/**
 * handle_interactive_mode - Handles the interactive mode of the shell
 *
 * Return: None
 */
void handle_interactive_mode(void)
{
	char *input = NULL;
	size_t input_len = 0;
	ssize_t read_len;

	while (1)
	{
		write(STDOUT_FILENO, "$ ", 2);
		read_len = getline(&input, &input_len, stdin);

		if (read_len == -1)
		{
			write(1, "\n", 1);
			free(input);
			free_dirs();
			exit(EXIT_FAILURE);
		}

		if (read_len > 0 && input[read_len - 1] == '\n')
			input[read_len - 1] = '\0';

		command_handle(input);
	}
}

/**
 * handle_non_interactive_mode - Handles the non-interactive mode of the shell
 *
 * Return: None
 */
void handle_non_interactive_mode(void)
{
	char *input = NULL;
	size_t input_len = 0;
	ssize_t read_len;

	input = (char *)malloc(input_len);
	if (!input)
	{
		perror("malloc");
		free(input);
		free_dirs();
		exit(EXIT_FAILURE);
	}
	while ((read_len = getline(&input, &input_len, stdin)) != -1)
	{
		if (read_len > 0 && input[read_len - 1] == '\n')
			input[read_len - 1] = '\0';

		command_handle(input);
	}
}
