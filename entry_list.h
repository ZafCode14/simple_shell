#ifndef _STRING_LIST_H_
#define _STRING_LIST_H_

/**
 * struct entry_node - a struct that represenent an entry[key/value]
 * @key: key
 * @value: value
 * @next: next entry node
 */
typedef struct entry_node
{
	char *key;
	char *value;
	struct entry_node *next;
} entry_node_t;

entry_node_t *_allocate_entry_node(const char *key, const char *value);
int _push_entry_node(entry_node_t **head, const char *key, const char *value);
int _delete_entry_node(entry_node_t **head, const char *key);

entry_node_t *_search_entry_list(entry_node_t *head, const char *key);
int _free_entry_list(entry_node_t **head);

size_t _length_entry_list(entry_node_t *head);

#endif
