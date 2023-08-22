#include "shell.h"

/**
 * _handle_command - a function that commands using _exec()
 * @input: the input string
 * @state: state of the shell
 *
 * Description: the function will do some adjusment to the input
 * then break down it to portions then sub command
 * then execute the sub command using _exec()
 * [input]: [portion]*
 * [portion]: [sub command]*
 * sub commands within the portions are separated by || or &&
 * Return: 0 on success
 */
int _handle_command(char *input, state_t *state)
{
	tk_info_t **portions, **sub_commands;
	int i = 0;
	char *delims[] = {";", NULL};
	char *delims_or_and[] = {"||", "&&", NULL};

#ifdef DEBUG
	printf("[input] %s<<\n", input);
#endif
	portions = tokenize(input, delims);

	while (portions[i] != NULL)
	{
#ifdef DEBUG
		printf("[portion] %s<<\n", portions[i]->str);
#endif
		sub_commands = tokenize(portions[i]->str, delims_or_and);

		_handle_sub_command(sub_commands, state);

		_free_token_info_array(sub_commands);

		++i;
	}

	_free_token_info_array(portions);

	return (0);
}

/**
 * _handle_sub_command - a function that execute the commands using _exec()
 * @sub_commands: tk_info_t * array
 * @state: state of the shell
 * Description: a _handle_command() helper
 */
void _handle_sub_command(tk_info_t **sub_commands, state_t *state)
{
	int j = 0;

	while (sub_commands[j] != NULL)
	{
#ifdef DEBUG
		printf(" [subcmd] %s<<\n", sub_commands[j]->str);
#endif
		if (j > 0)
		{
#ifdef DEBUG
			printf(" -> OR last status %d\nn", state->last_cmd_status);
			printf(" -> Operator %#x\nn", sub_commands[j - 1]->flags);
#endif
			if (sub_commands[j]->flags == DELIM(0))
				if (state->last_cmd_status == 0)
				{
					++j;
					continue;
				}
			if (sub_commands[j]->flags ==  DELIM(1))
				if (state->last_cmd_status != 0)
				{
					++j;
					continue;
				}
		}
		state->args = NULL;
		state->args = _parse_command(sub_commands[j]->str, state);
		if (state->args[0])
		{
			_exec(state);
		}
		_free_args(state->args), ++j;
	}
}
