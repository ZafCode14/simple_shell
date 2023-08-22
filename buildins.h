#ifndef _BUILDINS_H_
#define _BUILDINS_H_

#include "state.h"
/**
 * struct buildin - buildin struct
 * @command: command string
 * @callback: buildin callback ptr
 */
typedef struct buildin
{
	char *command;
	int (*callback)(state_t *);
} buildin_t;

/*buildins*/
int (*_select_buildin(const char *command))(state_t *);
int _hnd_env(state_t *state);
int _hnd_exit(state_t *state);
int _hnd_setenv(state_t *state);
int _hnd_unsetenv(state_t *state);
int _hnd_cd(state_t *state);
int _hnd_alias(state_t *state);
#endif
