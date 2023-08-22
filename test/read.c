 #include "../shell.h"

int main()
{
	int fd = open("test/script", O_RDONLY);
	char * line = NULL;
	size_t size = 0;

	while(1)
	{
		line = NULL, size = 0;
		if (_getline(&line, &size, STDIN_FILENO) < 0)
		{
			perror("OHMY");
			printf("->end\n");
			break;
		}
		printf("line: %s", line);
		free(line);
	}
	return (0);
}
