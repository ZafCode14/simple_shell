#include "shell.h"

/**
 * linked_dirs - creates a linked list
 * @var: pointer to the variable in the environment
 * @head: pointer to pointer to the head node
 *
 * Return: pointer to the head node
 */
list_t *linked_dirs(char *var, list_t **head)
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

		if (*head == NULL)
		{
			*head = new;
			tail = new;
		}
		else
		{
			tail->next = new;
			tail = new;
		}

		token = strtok(NULL, delim);
	}
	return (*head);
}

/**
 * free_list - frees a linked list
 * @head: pointer to the head node
 *
 * Return: void
 */
void free_list(list_t *head)
{
	list_t *current = head;
	list_t *next;

	while (current != NULL)
	{
		next = current->next;
		free(current->dir);
		free(current);
		current = next;
	}
}
