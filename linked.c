#include "shell.h"

/**
 * linked_dirs - creates a linked list
 * @var: pointer to the variable in the environment
 *
 * Return: pointer to the head node
 */
list_t *linked_dirs(char *var)
{
	char *value = getenv(var);
	char *delim = ":";
	char *token;
	list_t *new;
	list_t *tail = NULL;

	token = strtok(value, delim);
	while (token)
	{
		new = malloc(sizeof(list_t));
		if (new == NULL)
			return (NULL);

		new->dir = strdup(token);
		if (new->dir == NULL)
		{
			free(new);
			return (NULL);
		}

		new->next = NULL;

		if (dir_h == NULL)
		{
			dir_h = new;
			tail = new;
		}
		else
		{
			tail->next = new;
			tail = new;
		}

		token = strtok(NULL, delim);
	}
	return (dir_h);
}

/**
 * free_dirs - frees a linked list
 *
 * Return: void
 */
void free_dirs(void)
{
	list_t *current = dir_h;
	list_t *next;

	while (current != NULL)
	{
		next = current->next;
		free(current->dir);
		free(current);
		current = next;
	}
}
