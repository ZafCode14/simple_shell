#include "shell.h"

/**
 * exit_b - builtin exit command
 * @input: pointer to input string
 * @argv: pointer to an array of strings
 * @len: number of strings (input)
 * @dir_h: pointer to the head of dir linked list
 *
 * Return: void
 */
void exit_b(char *input, char *argv[], int len, dir_t *dir_h)
{
	if (_strcmp(argv[0], "exit") == 0 && len == 1)
	{
		free(input);
		free_dirs(dir_h);
		exit(EXIT_SUCCESS);
	}
	else if (_strcmp(argv[0], "exit") == 0 && len == 2)
	{
		int exit_status = _atoi(argv[1]);

		free(input);
		free_dirs(dir_h);
		exit(exit_status);
	}
}

/**
 * cd_b - builtin cd command
 * @argv: pointer to an array of strings
 * @len: number of strings (input)
 *
 * Return: void
 */
void cd_b(char *argv[], int len)
{
	char *home = _getenv("HOME");
	char *err = "Usage: cd [DIRECTORY]\n";
	char cwd[BUFFER_SIZE];
	char *prev_dir = _getenv("OLDPWD");

	if (_strcmp(argv[0], "cd") == 0 && len == 1)
	{
		getcwd(cwd, sizeof(cwd));
		_setenv("OLDPWD", cwd, 1);
		chdir(home);
		getcwd(cwd, sizeof(cwd));
		_setenv("PWD", cwd, 1);
	}
	else if (_strcmp(argv[0], "cd") == 0 &&
			_strcmp(argv[1], "-") == 0 && len == 2)
	{
		getcwd(cwd, sizeof(cwd));
		_setenv("OLDPWD", cwd, 1);
		chdir(prev_dir);
		getcwd(cwd, sizeof(cwd));
		_setenv("PWD", cwd, 1);
	}
	else if (_strcmp(argv[0], "cd") == 0 && len == 2)
	{
		getcwd(cwd, sizeof(cwd));
		_setenv("OLDPWD", cwd, 1);
		if (chdir(argv[1]) == -1)
			perror(argv[1]);
		getcwd(cwd, sizeof(cwd));
		_setenv("PWD", cwd, 1);
	}
	else if (_strcmp(argv[0], "cd") == 0 && (len != 1 || len != 2))
		write(STDERR_FILENO, err, _strlen(err));
}

/**
 * env_b - builtin env commands
 * @input: pointer to input string
 * @argv: pointer to an array of strings
 * @len: number of strings (input)
 *
 * Return: void
 */
void env_b(char *input, char *argv[], int len)
{
	char *err_senv = "Usage: setenv VARIABLE VALUE\n";
	char *err_usenv = "Usage: unsetenv VARIABLE\n";

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
