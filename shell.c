#include "shell.h"
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
	list_t *head = NULL;

	linked_dirs("PATH", &head);
	while (1)
	{
		write(STDOUT_FILENO, "$ ", 2);
		read_len = getline(&input, &input_len, stdin);

		if (read_len == -1)
		{
			printf("\n");
			free(input);
			exit(EXIT_FAILURE);
		}

		if (_strcmp(input, "exit\n") == 0)
		{
			free(input);
			exit(EXIT_SUCCESS);
		}
		if (read_len > 0 && input[read_len - 1] == '\n')
			input[read_len - 1] = '\0';

		command_handle(input, head);
	}
	free_list(head);
	free(input);
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
	list_t *head = NULL;

	input = (char *)malloc(input_len);
	linked_dirs("PATH", &head);
	if (!input)
	{
		perror("malloc");
		free(input);
		exit(EXIT_FAILURE);
	}
	while ((read_len = getline(&input, &input_len, stdin)) != -1)
	{
		if (read_len > 0 && input[read_len - 1] == '\n')
			input[read_len - 1] = '\0';

		command_handle(input, head);
	}
	free_list(head);
	free(input);
}

/**
 * main - entry point
 *
 * Return: 0
 */
int main(void)
{
	int interactive = isatty(STDIN_FILENO);

	if (interactive)
		handle_interactive_mode();
	else
		handle_non_interactive_mode();

	return (0);
}
