#include "shell.h"

/**
 * command_handle - handles the command
 * @input: pointer to the input string
 * @dir_h: pointer to head node of PATH directories
 *
 * Return: void
 */
void command_handle(char *input, dir_t *dir_h)
{
	int i;
	char *delim = " ", *token, *argv[BUFFER_SIZE] = {NULL};

	if (strlen(input) > 0)
	{
		token = strtok(input, delim);
		for (i = 0; token; i++)
		{
			argv[i] = token;
			token = strtok(NULL, delim);
		}
		handle_builtins(input, argv, i, dir_h);
		search_command(input, argv, dir_h);
	}
}

/**
 * handle_builtins - handles the built-in commands
 * @argv: pointer to an array of input strings
 * @len: number of arguments in the array of strings
 * @input: pointer to the input command
 * @dir_h: pointer to head node of PATH directories
 *
 * Return: void
 */
void handle_builtins(char *input, char *argv[], int len, dir_t *dir_h)
{
	exit_b(input, argv, len, dir_h);
	cd_b(argv, len);
	env_b(input, argv, len);
}

/**
 * search_command - searches for the command in the PATH directories
 * @input: pointer to the inputed command
 * @argv: pointer to an array of strings
 * @dir_h: pointer to head node of PATH directories
 *
 * Return: void
 */
void search_command(char *input, char *argv[], dir_t *dir_h)
{
	struct stat st;
	int command_found = 0, builtin_found = 0;
	char path[BUFFER_SIZE];
	dir_t *temp = dir_h;

	if (
	_strcmp(argv[0], "env") == 0 || _strcmp(argv[0], "setenv") == 0 ||
	_strcmp(argv[0], "unsetenv") == 0 || _strcmp(argv[0], "exit") == 0 ||
	_strcmp(argv[0], "cd") == 0
		)
		builtin_found = 1;
	if (stat(argv[0], &st) == 0)
	{
		_strcpy(path, argv[0]);
		command_found = 1;
	}
	else
	{
		for (; temp; temp = temp->next)
		{
			_strcpy(path, temp->dir);
			_strcat(path, "/");
			_strcat(path, argv[0]);
			if (stat(path, &st) == 0)
			{
				command_found = 1;
				break;
			}
		}
	}
	if (builtin_found)
		return;
	else if (command_found)
		found(input, argv, path, dir_h);
	else if (!command_found)
	{
		char *err = _strcat(argv[0], ": command not found\n");

		write(STDERR_FILENO, err, _strlen(err));
	}
}

/**
 * found - executes the found command
 * @input: pointer to the inputed command
 * @argv: pointer to an array of string
 * @path: pointer to the path where the command is found
 * @dir_h: pointer to head node of PATH directories
 *
 * Return: void
 */
void found(char *input, char *argv[], char *path, dir_t *dir_h)
{
	pid_t pid;

	pid = fork();
	if (pid == -1)
	{
		perror("fork");
		free(input);
		free_dirs(dir_h);
		exit(EXIT_FAILURE);
	}
	if (pid == 0)
	{
		if (execve(path, argv, environ) == -1)
		{
			perror("execve");
			free(input);
			free_dirs(dir_h);
			exit(EXIT_FAILURE);
		}
	}
	else
		wait(NULL);
}
