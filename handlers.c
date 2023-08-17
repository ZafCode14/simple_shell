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
	struct stat st;
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

		handle_builtins(input, head);

		if (stat(argv[0], &st) == 0)
			full_path_command(input, argv, head);
		else
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
void handle_builtins(char *input, list_t *head)
{
	int j = 0;

	if (_strcmp(input, "exit") == 0)
	{
		free(input);
		free_list(head);
		exit(EXIT_SUCCESS);
	}

	if (_strcmp(input, "env") == 0)
	{
		while (environ[j] != NULL)
		{
			printf("%s\n", environ[j]);
			j++;
		}
	}
}

/**
 * full_path_command - executes when the full path of the command is passed
 * @input: pointer to the inputed command
 * @head: pointer to the head of linked list of PATH directories
 * @argv: pointer to an array of string
 *
 * Return: void
 */
void full_path_command(char *input, char *argv[], list_t *head)
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
		if (execve(argv[0], argv, NULL) == -1)
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

	while (temp)
	{
		strcpy(path, temp->dir);
		strcat(path, "/");
		strcat(path, argv[0]);
		if (stat(path, &st) == 0)
		{
			command_found = 1;
			break;
		}
		path[0] = '\0';
		temp = temp->next;
	}
	if (command_found)
		found(input, argv, head, path);
	else if (!command_found)
		printf("%s: command not found\n", argv[0]);
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
		if (execve(path, argv, NULL) == -1)
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
