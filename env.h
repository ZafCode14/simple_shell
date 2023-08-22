#ifndef _ENV_H_
#define _ENV_H_
#include "entry_list.h"

int _init_env_list(entry_node_t **head, char **environ);
char **_construct_env_table(entry_node_t *head);
char *_construct_env_entry(const char *key, const char *value);
const char *_get_value(entry_node_t *head, const char *key);
void _free_env_table(char **table);

#endif

