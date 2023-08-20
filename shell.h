#ifndef SHELL_H
#define SHELL_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>

#define BUFFER_SIZE 1024

extern char **environ;

/**
 * struct node - singly linked list
 * @dir: string - (malloc'ed string)
 * @next: points to the next node
 *
 * Description: singly linked list node structure
 */
typedef struct node
{
	char *dir;
	struct node *next;
} list_t;
list_t *dir_h;

/* shell.c */
int main(void);
void handle_interactive_mode(void);
void handle_non_interactive_mode(void);

/* handlers.c */
void command_handle(char *input);
void handle_builtins(char *input, char *argv[], int len);
void search_command(char *input, char *argv[]);
void found(char *input, char *argv[], char *path);

/* env.c */
int _setenv(const char *name, const char *value, int overwrite);
int _unsetenv(const char *name);

/* linked.c */
list_t *linked_dirs(char *var);
void free_dirs(void);

/* strings.c */
int _strcmp(char *s1, char *s2);
int _strlen(char *s);
int _strncmp(const char *s1, const char *s2, size_t n);
char *_strcpy(char *dest, char *src);
char *_strcat(char *dest, char *src);
int _atoi(char *s);

/* getenv.c */
char *_getenv(const char *name);

#endif /* SHELL_H */
