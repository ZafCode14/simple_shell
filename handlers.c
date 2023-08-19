#include "shell.h"

/**
 * command_handle - handles the command
 * @input: pointer to the input string
 * @head: pointer to the head of the linked list of the PATH directories
 *
 * Return: void
 */
void command_handle(char *input, list_t *head)
{
	int i;
	char *delim = " ", *token, *argv[20] = {NULL};

	if (strlen(input) > 0)
	{
		token = strtok(input, delim);
		for (i = 0; token && i < 20; i++)
		{
			argv[i] = token;
			token = strtok(NULL, delim);
		}

		handle_builtins(input, argv, i, head);

		search_command(input, argv, head);
	}
}

/**
 * handle_builtins - handles the built-in commands
 * @input: pointer to the input command
 * @head: pointer to the head node of linked list of PATH directories
 *
 * Return: void
 */
void handle_builtins(char *input, char *argv[], int len, list_t *head)
{
	if (_strcmp(argv[0], "exit") == 0 && len == 1)
	{
		free(input);
		free_list(head);
		exit(EXIT_SUCCESS);
	}
	else if (_strcmp(argv[0], "exit") == 0 && len == 2)
	{
		int exit_status = _atoi(argv[1]);

		free(input);
		free_list(head);
		exit(exit_status);
	}
}

/**
 * search_command - searches for the command in the PATH directories
 * @input: pointer to the inputed command
 * @head: pointer to the head of linked list of PATH dierectories
 * @argv: pointer to an array of strings
 *
 * Return: void
 */
void search_command(char *input, char *argv[], list_t *head)
{
	struct stat st;
	int command_found = 0;
	char path[BUFFER_SIZE];
	list_t *temp = head;

	if (stat(argv[0], &st) == 0)
	{
		_strcpy(path, argv[0]);
		command_found = 1;
	}
	else
	{
		while (temp)
		{
			_strcpy(path, temp->dir);
			_strcat(path, "/");
			_strcat(path, argv[0]);
			if (stat(path, &st) == 0)
			{
				command_found = 1;
				break;
			}
			temp = temp->next;
		}
	}
	if (command_found)
		found(input, argv, head, path);
	else if (!command_found)
		perror(argv[0]);
}

/**
 * found - executes the found command
 * @input: pointer to the inputed command
 * @head: pointer to the head of linked list of PATH directories
 * @argv: pointer to an array of string
 * @path: pointer to the path where the command is found
 *
 * Return: void
 */
void found(char *input, char *argv[], list_t *head, char *path)
{
	pid_t pid;

	pid = fork();
	if (pid == -1)
	{
		perror("fork");
		free(input);
		free_list(head);
		exit(EXIT_FAILURE);
	}
	if (pid == 0)
	{
		if (execve(path, argv, environ) == -1)
		{
			perror("execve");
			free(input);
			free_list(head);
			exit(EXIT_FAILURE);
		}
	}
	else
		wait(NULL);
}
