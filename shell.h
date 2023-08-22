#ifndef _SHELL_H_
#define _SHELL_H_

#include <unistd.h>
#include <fcntl.h>
#include <dirent.h>
#include <errno.h>
#include <signal.h>

#include <string.h>
#include <stdlib.h>
#include <stdio.h>

#include <sys/wait.h>

#include "env.h"
#include "entry_list.h"
#include "numbers.h"
#include "str.h"
#include "token.h"
#include "buildins.h"
#include "path.h"
#include "state.h"
#include "io.h"
#include "errors.h"

#define BUFF_SIZE 1024
#define SHELL_NAME (_get_shell_name(NULL))

extern int errno;
extern char **environ;

void _lanch_shell(state_t *state);

ssize_t _getline(char **lineptr, size_t *n, int fd);
void _cut_comments(char *input);
char **_parse_command(char *input, state_t *state);
void _handle_variables(state_t *state);
void _free_args(char **args);

int _handle_command(char *input, state_t *state);
void _handle_sub_command(tk_info_t **sub_commands, state_t *state);
int _exec(state_t *state);

char *_get_shell_name(const char *name);
void _print_cursor(void);

#endif
