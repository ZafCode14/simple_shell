#include "shell.h"

char *_alias_get_key(const char *entry);
char *_alias_get_value(const char *entry);
/**
 * _hnd_alias -  call back that handle alias buildin
 * @state: shell state
 * Return: 0 on success
 */
int _hnd_alias(state_t *state)
{
	entry_node_t *curr = NULL;

	if (state->args[1] == NULL)
	{
		curr = state->alias_head;
		while (curr)
		{
			printf("%s", curr->key);
			printf("=");
			printf("'%s'\n", curr->value);
			curr = curr->next;
		}
	}
	else
	{
		int i = 1;

		while (state->args[i])
		{
#ifdef DEBUG
			printf(" -> %s\n", state->args[i]);
#endif
			if (strchr(state->args[i], '=')) /*we add*/
			{
				char *key = NULL;
				char *value = NULL;

				key = _alias_get_key(state->args[i]);
				value = _alias_get_value(state->args[i]);
				_push_entry_node(&(state->alias_head), key, value);

				free(key);
				free(value);
			}
			else /*we print*/
			{
				entry_node_t *node;

				node = _search_entry_list(state->alias_head, state->args[i]);
				if (node)
				{
					printf("%s", node->key);
					printf("=");
					printf("'%s'\n", node->value);
				}
			}
			++i;
		}
	}
	state->last_cmd_status = 0;
	return (0);
}
/**
 * _alias_get_key -  a function that extract the key from the args
 * @entry: args entry
 * Return: malloc'd key
 */
char *_alias_get_key(const char *entry)
{
	int i = 0;
	char *key = NULL;

	while (entry[i] != '\0' && entry[i] != '=')
	{
		++i;
	}

	key = malloc(i + 1);
	key[i] = '\0';
	strncpy(key, entry, i);
	return (key);
}
/**
 * _alias_get_value - a function that extract the value from the args
 * @entry: args entry
 * Return: malloc'd value
 */
char *_alias_get_value(const char *entry)
{
	int i = 0;
	char *value = NULL;
	int len = 0;

	value = malloc(BUFF_SIZE);
	while (entry[i] != '\0' && entry[i] != '=')
	{
		++i;
	}

	if (entry[i] != '\0')
		++i;
	while (entry[i] != '\0')
	{
		if (entry[i] != '\'')
		{
			value[len] = entry[i];
			++len;
		}
		++i;
	}
	value[len] = '\0';

	return (value);
}
