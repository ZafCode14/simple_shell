#include "shell.h"

/**
 * _allocate_entry_node - mallocte a entry_node
 * @key: key
 * @value: value
 * Return: ptr to the allocated node or NULL
 */
entry_node_t *_allocate_entry_node(const char *key, const char *value)
{
	entry_node_t *node = NULL;

	node = malloc(sizeof(entry_node_t));
	if (!node)
		return (NULL);

	node->key = strdup(key);
	node->value = (value) ? strdup(value) : NULL;
	node->next = NULL;

	return (node);
}

/**
 * _push_entry_node - push a node to a entry list
 * @head: head of the list
 * @key: key
 * @value: value
 * Return: 0 on succses -1 on failure
 */
int _push_entry_node(entry_node_t **head, const char *key, const char *value)
{
	entry_node_t *curr = NULL;
	entry_node_t *node = NULL;
	entry_node_t *target = NULL;

	if (head == NULL || key == NULL)
		return (-1);

	target = _search_entry_list(*head, key);

	if (target) /*the var already exist*/
	{

		free(target->key);
		free(target->value);
		target->key = strdup(key);
		target->value = (value) ? strdup(value) : NULL;
		return (0);
	}

	curr = *head;
	/*allocat a new nod as it does not exist*/
	node = _allocate_entry_node(key, value);
	if (node == NULL)
		return (-1);

	/*a new entry*/
	if (curr == NULL) /*curr aka *head is null*/
	{
		*head = node;
	}
	else /*the list is full*/
	{
		while (curr->next != NULL) /*we search for the tail*/
			curr = curr->next;
		curr->next = node;
	}
	return (0);
}

/**
 * _search_entry_list - fetch node using a key from an entry list
 * @head: head of a list
 * @key: key
 * Return: ptr to the node if found or NULL
 */
entry_node_t *_search_entry_list(entry_node_t *head, const char *key)
{
	while (head)
	{
		if (strcmp(head->key, key) == 0)
			return (head);
		head = head->next;
	}
	return (NULL);
}

/**
 * _delete_entry_node - delete node from an entry list
 * @head: head of a list
 * @key: key
 * Return: 0 on success or -1
 */
int _delete_entry_node(entry_node_t **head, const char *key)
{
	entry_node_t *curr = NULL;
	entry_node_t *target = NULL;

	if (head == NULL || *head == NULL)
		return (-1);

	curr = *head;
	target = _search_entry_list(*head, key);

	if (target == *head)
	{
		*head = target->next;
		free(target->key);
		free(target->value);
		free(target);
	}
	else
	{
		while (curr && curr->next)
		{
			if (curr->next == target)
			{
				curr->next = target->next;
				free(target->key);
				free(target->value);
				free(target);
				break;
			}
			curr = curr->next;
		}
	}
	return (0);
}

/**
 * _free_entry_list - free an entry list
 * @head: head of the list
 * Return: 0 on success
 */
int _free_entry_list(entry_node_t **head)
{
	entry_node_t *curr = NULL;
	entry_node_t *next = NULL;

	curr = *head;
	while (curr)
	{
		free(curr->key);
		free(curr->value);
		next = curr->next;
		free(curr);
		curr = next;
	}

	*head = NULL;
	return (0);
}
