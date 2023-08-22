#include "../shell.h"

int main(void)
{
	env_node_t *head = NULL;
	env_node_t *curr = NULL;
	char **env = NULL;
	int i = 0;
	
	if(_init_env_list(&head, environ) < 0)
	{
		printf ("init\n");
	}
		
	printf ("%s\n", _search_env_list(head, "PATH")->entry);
	_delete_env_node(&head, "LESSOPEN");
	_delete_env_node(&head, "LS_COLORS");
	_push_env_node(&head, "LAGZAL=");
	curr = head;
	while (curr)
	{
		printf("%s\n", curr->entry);
		curr = curr->next;
	}
	env = _construct_env_table(head);
	while (env && env[i])
	{
		printf("%s\n", env[i]);
		++i;
	}
	free(env);
	_free_env_list(&head);
	return (0);
}
