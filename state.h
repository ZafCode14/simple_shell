#ifndef _STATE_H_
#define _STATE_H_


#define INTERACTIVE_MODE 1
#define NO_INTERACTIVE_MODE 2
#define SCRIPT_MODE 3
/**
 * struct shell_state - info stat
 * @args: args of the program
 * @running: running flag
 * @fd_input: the input of the shell
 * @last_cmd_status: the status/ exit code of the last command
 * @pid: proccess id of the shell
 * @shell_name: shell name
 * @shell_argv: shell program argv
 * @alias_head: alias entry list head
 * @env_head: env entry list head;
 * @environ: ptr to the environ array
 */
typedef struct shell_state
{
	char **args;

	int running;
	int fd_input;

	int last_cmd_status;
	int pid;

	char *shell_name;
	char **shell_argv;

	entry_node_t *alias_head;

	entry_node_t *env_head;
	char ***environ;
} state_t;

void _init_state(state_t *state);
void _free_state(state_t *state);

#endif
