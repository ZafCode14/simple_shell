#include "../shell.h"

extern char **environ;

int main(void)
{
	char env[1024];

	getcwd(env, 1024);
	printf("%s\n", env);

	chdir("test");
	getcwd(env, 1024);
	printf("%s\n", env);
	return (0);
}
