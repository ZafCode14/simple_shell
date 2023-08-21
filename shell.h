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
 * struct dirs - singly linked list
 * @dir: string - (malloc'ed string)
 * @next: points to the next node
 *
 * Description: singly linked list node structure
 */
typedef struct dirs
{
	char *dir;
	struct dirs *next;
} dir_t;

/* shell.c */
int main(void);
void handle_interactive_mode(dir_t *dir_h);
void handle_non_interactive_mode(dir_t *dir_h);

/* handlers.c */
void command_handle(char *input, dir_t *dir_h);
void handle_builtins(char *input, char *argv[], int len, dir_t *dir_h);
void search_command(char *input, char *argv[], dir_t *dir_h);
void found(char *input, char *argv[], char *path, dir_t *dir_h);

/* builtins.c */
void exit_b(char *input, char *argv[], int len, dir_t *dir_h);
void cd_b(char *argv[], int len);
void env_b(char *input, char *argv[], int len);

/* env.c */
int _setenv(const char *name, const char *value, int overwrite);
int _unsetenv(const char *name);
char *_getenv(const char *name);

/* linked.c */
dir_t *linked_dirs(char *var, dir_t **dir_h);
void free_dirs(dir_t *dir_h);

/* strings.c */
int _strcmp(char *s1, char *s2);
int _strlen(char *s);
int _strncmp(const char *s1, const char *s2, size_t n);
char *_strcpy(char *dest, char *src);
char *_strcat(char *dest, char *src);

/* strings2.c */
int _atoi(char *s);

#endif /* SHELL_H */
