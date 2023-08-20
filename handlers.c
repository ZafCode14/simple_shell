#include "shell.h"

/**
 * command_handle - handles the command
 * @input: pointer to the input string
 *
 * Return: void
 */
void command_handle(char *input)
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
		handle_builtins(input, argv, i);
		search_command(input, argv);
	}
}

/**
 * handle_builtins - handles the built-in commands
 * @argv: pointer to an array of input strings
 * @len: number of arguments in the array of strings
 * @input: pointer to the input command
 *
 * Return: void
 */
void handle_builtins(char *input, char *argv[], int len)
{
	char *err_senv = "Usage: setenv VARIABLE VALUE\n";
	char *err_usenv = "Usage: setenv VARIABLE\n";

	if (_strcmp(argv[0], "exit") == 0 && len == 1)
	{
		free(input);
		free_dirs();
		exit(EXIT_SUCCESS);
	}
	else if (_strcmp(argv[0], "exit") == 0 && len == 2)
	{
		int exit_status = _atoi(argv[1]);

		free(input);
		free_dirs();
		exit(exit_status);
	}
	if (_strcmp(input, "env") == 0)
	{
		int i = 0;

		while (environ[i])
		{
			write(STDOUT_FILENO, environ[i], _strlen(environ[i]));
			write(STDOUT_FILENO, "\n", 1);
			i++;
		}
	}
	if (_strcmp(argv[0], "setenv") == 0 && len == 3)
		_setenv(argv[1], argv[2], 1);
	else if (_strcmp(argv[0], "setenv") == 0 && len != 3)
		write(STDERR_FILENO, err_senv, _strlen(err_senv));

	if (_strcmp(argv[0], "unsetenv") == 0 && len == 2)
		_unsetenv(argv[1]);
	else if (_strcmp(argv[0], "unsetenv") == 0 && len != 2)
		write(STDERR_FILENO, err_usenv, _strlen(err_usenv));
}

/**
 * search_command - searches for the command in the PATH directories
 * @input: pointer to the inputed command
 * @argv: pointer to an array of strings
 *
 * Return: void
 */
void search_command(char *input, char *argv[])
{
	struct stat st;
	int command_found = 0, builtin_found = 0;
	char path[BUFFER_SIZE];
	list_t *temp = dir_h;

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
		found(input, argv, path);
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
 *
 * Return: void
 */
void found(char *input, char *argv[], char *path)
{
	pid_t pid;

	pid = fork();
	if (pid == -1)
	{
		perror("fork");
		free(input);
		free_dirs();
		exit(EXIT_FAILURE);
	}
	if (pid == 0)
	{
		if (execve(path, argv, environ) == -1)
		{
			perror("execve");
			free(input);
			free_dirs();
			exit(EXIT_FAILURE);
		}
	}
	else
		wait(NULL);
}
