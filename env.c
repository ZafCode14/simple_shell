#include "shell.h"

/**
 * _init_env_list - a function that init a entry node using a array of entries
 * @head: head of the list to be created
 * @environ: the char ** that hold the entries
 *
 * Description: that function is used to init the env_head in the shell state
 * at the start of the program so that manipilating the env entries
 * becomes easier.
 * Return: 0 on success
 */
int _init_env_list(entry_node_t **head, char **environ)
{

	if (head == NULL)
		return (-1);

	while (*environ != NULL)
	{
		size_t key_end  = 0;

		while ((*environ)[key_end] != '\0' && (*environ)[key_end] != '=')
			++key_end;
		if ((*environ)[key_end] == '=')
		{
			(*environ)[key_end] = '\0';
			++key_end;
		}
		_push_entry_node(head, *environ, *environ + key_end);
		++environ;
	}
	return (1);
}

/**
 * _construct_env_table - construct an char ** array that hold env entries
 * @head: head of the entry list based on witch the table will be created
 * Return: ptr to the malloc allocated table or NULL
 */
char **_construct_env_table(entry_node_t *head)
{
	size_t len = _length_entry_list(head);
	char **table = NULL;
	size_t i = 0;

	table = malloc(sizeof(char *) * (len + 1));
	if (table == NULL)
	{
		perror(NULL);
		return (NULL);
	}

	table[len] = NULL;
	while (i < len)
	{
		table[i] = _construct_env_entry(head->key, head->value);

		++i;
		head = head->next;
	}

	return (table);
}

/**
 * _construct_env_entry - construct a hard allocated env entry node
 * @key: key
 * @value: value
 * Description: [Entry]: [key]=[value]
 * Return: ptr to the entry or NULL
 */
char *_construct_env_entry(const char *key, const char *value)
{
	char *entry = NULL;
	size_t size = 2;

	if (key)
		size += strlen(key);
	if (value)
		size += strlen(value);

	entry = malloc(size);
	entry[0] = '\0';
	strcat(entry, key);
	strcat(entry, "=");

	if (value)
	{
		strcat(entry, value);
	}

	return (entry);
}
/**
 * _free_env_table - free a table allocated using _construct_env_table()
 * @table: ptr to the table
 */
void _free_env_table(char **table)
{
	int i = 0;

	while (table[i])
	{
		free(table[i]);
		++i;
	}
	free(table);
}

/**
 * _get_value - get a entry value
 * @head: entry list
 * @key: search key
 * Return: NULL or const char of the value
 */
const char *_get_value(entry_node_t *head, const char *key)
{
	entry_node_t *node = _search_entry_list(head, key);

	if (node)
		return (node->value);
	return (NULL);
}
