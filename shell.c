#include "main.h"

/**
 * command_handle - handles the command
 * @input: pointer to the input string
 * @av: argument value
 *
 * Return: void
 */
void command_handle(char *input, char *av[])
{
	int i;
	char *delim = " ";
	char *token;
	char *argv[20] = {NULL};
	pid_t pid;

	if (strlen(input) > 0)
	{
		token = strtok(input, delim);
		for (i = 0; token && i < 20; i++)
		{
			argv[i] = token;
			token = strtok(NULL, delim);
		}
		pid = fork();
		if (pid == -1)
		{
			perror("fork");
			exit(EXIT_FAILURE);
		}
		if (pid == 0)
		{
			if (execve(argv[0], argv, NULL) == -1)
			{
				perror(av[0]);
				exit(EXIT_FAILURE);
			}
		}
		else
			wait(NULL);
	}
}

/**
 * handle_interactive_mode - Handles the interactive mode of the shell
 * @av: Argument vector
 *
 * Return: None
 */
void handle_interactive_mode(char *av[])
{
	char *input = NULL;
	size_t input_len = 0;
	ssize_t read_len;

	while (1)
	{
		printf("$ ");
		read_len = getline(&input, &input_len, stdin);

		if (read_len == -1)
		{
			printf("\n");
			exit(EXIT_FAILURE);
		}

		if (strcmp(input, "exit\n") == 0)
		{
			free(input);
			exit(EXIT_SUCCESS);
		}

		if (read_len > 0 && input[read_len - 1] == '\n')
			input[read_len - 1] = '\0';

		command_handle(input, av);
	}
	free(input);
}

/**
 * handle_non_interactive_mode - Handles the non-interactive mode of the shell
 * @av: Argument vector
 *
 * Return: None
 */
void handle_non_interactive_mode(char *av[])
{
	char *input = NULL;
	size_t buffer_size = 1024;
	ssize_t read_len;

	input = (char *)malloc(buffer_size);
	if (!input)
	{
		perror("malloc");
		exit(EXIT_FAILURE);
	}

	while ((read_len = getline(&input, &buffer_size, stdin)) != -1)
	{
		if (read_len > 0 && input[read_len - 1] == '\n')
			input[read_len - 1] = '\0';

		command_handle(input, av);
	}

	free(input);
}

/**
 * main - entry point
 * @ac: argument count
 * @av: argument value
 *
 * Return: 0
 */
int main(int ac, char *av[])
{
	int interactive = isatty(STDIN_FILENO);
	(void)ac;

	if (interactive)
		handle_interactive_mode(av);
	else
		handle_non_interactive_mode(av);

	return (0);
}
