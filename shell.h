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

/* shell.c */
int main(void);
void handle_interactive_mode(void);
void handle_non_interactive_mode(void);

/* handlers.c */
void command_handle(char *input, list_t *head);
void handle_builtins(char *input, char *argv[], int len, list_t *head);
void search_command(char *input, char *argv[], list_t *head);
void found(char *input, char *argv[], list_t *head, char *path);

/* linked.c */
list_t *linked_dirs(char *var, list_t **head);
void free_list(list_t *head);

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
