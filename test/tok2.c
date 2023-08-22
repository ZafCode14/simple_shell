#include "../str.h"
#include <stdio.h>

int main(void)

{
	char *delims[] = {
		"||",
		"&&",
		NULL
	};

	char input[] = "A||B&&C";
	int witch_one = 0;
	char *token = NULL;

	token = strtok2(input, delims, &witch_one);

	while (token != NULL)
	{
		printf("token: %s[%d]\n", token, witch_one);
		token = strtok2(NULL, delims, &witch_one);
	}
	return (0);
}
