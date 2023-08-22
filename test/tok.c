#include "../shell.h"

int main(void)
{
	char string[] = ";;;;;;;;ls;;echo;;aa;;";
	char *delims[] = {";", NULL};
	int i = 0;

	tk_info_t **tokens = tokenize(string, delims);
	while (tokens[i])
	{
		printf("%s\n", tokens[i]->str);
		++i;
	}
	free(tokens);

	return (0);
}
