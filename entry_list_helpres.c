#include "shell.h"

/**
 * _length_entry_list - returns the length of a entry list
 * @head: head of the list
 * Return: len
 */
size_t _length_entry_list(entry_node_t *head)
{
	size_t r = 0;

	while (head != NULL)
	{
		++r;
		head = head->next;
	}
	return (r);
}
