#include "shell.h"

/**
 * linked_dirs - creates a linked list
 * @var: pointer to the variable in the environment
 * @dir_h: pointer to pointer to head node of PATH directories
 *
 * Return: pointer to the head node
 */
dir_t *linked_dirs(char *var, dir_t **dir_h)
{
	char *value = getenv(var);
	char *delim = ":";
	char *token;
	dir_t *new;
	dir_t *temp = NULL;

	token = strtok(value, delim);
	while (token)
	{
		new = malloc(sizeof(dir_t));
		if (new == NULL)
			return (NULL);

		new->dir = strdup(token);
		if (new->dir == NULL)
		{
			free(new);
			return (NULL);
		}

		new->next = NULL;

		if (*dir_h == NULL)
		{
			*dir_h = new;
			temp = new;
		}
		else
		{
			temp->next = new;
			temp = new;
		}

		token = strtok(NULL, delim);
	}
	return (*dir_h);
}

/**
 * free_dirs - frees a linked list
 * @dir_h: pointer to head node of PATH directories
 *
 * Return: void
 */
void free_dirs(dir_t *dir_h)
{
	dir_t *current = dir_h;
	dir_t *next;

	while (current != NULL)
	{
		next = current->next;
		free(current->dir);
		free(current);
		current = next;
	}
}
