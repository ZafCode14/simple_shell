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

list_t *linked_dirs(char *var, list_t **head);
void free_list(list_t *head);
size_t print_list(const list_t *h);

char *_getenv(const char *name);
void command_handle(char *input, list_t *head);

int _strcmp(char *s1, char *s2);
int _strlen(char *s);
int _strncmp(const char *s1, const char *s2, size_t n);
char *_strcpy(char *dest, char *src);

#endif /* SHELL_H */
