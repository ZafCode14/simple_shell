#include "shell.h"

/**
 * _init_state - init the state struct at the start of the program
 * @state: shell state ptr
 */
void _init_state(state_t *state)
{
	state->running = 1;
	state->pid = getpid();
	state->last_cmd_status = 0;

	state->env_head = NULL;
	_init_env_list(&(state->env_head), environ);
	state->environ = &environ;
	*(state->environ) = _construct_env_table(state->env_head);

	state->alias_head = NULL;
}

/**
 * _free_state - free the state struct at the end of the program
 * @state: state ptr
 */
void _free_state(state_t *state)
{
	_free_entry_list(&(state->env_head));
	_free_entry_list(&(state->alias_head));
	_free_env_table(*(state->environ));
}
