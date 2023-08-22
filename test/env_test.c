#include "../shell.h"

int main(void)
{
	env_node_t *head = NULL;
	env_node_t *curr = NULL;

	_push_env_node(&head, "HEAD");
	_push_env_node(&head, "HEAD^1");
	
	curr = head;
	while (curr)
	{
		printf("%s\n", curr->entry);
		curr = curr->next;
	}
	_free_env_list(&head);

	return (0);
}
