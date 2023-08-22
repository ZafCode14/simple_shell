#include "shell.h"

/**
 * _parse_command - parse command string into args
 * @input: a var that hold the command string
 * @state: the shell state
 *
 * Description: it actually parse the sub command in our terminology
 * args[0] hold the name of the program [while handling the alias it
 * appear that args should be hard in memory cuz tokenis will alter
 * the value of alias value witch we dont want]
 * Return: return char **
 */
char **_parse_command(char *input, state_t *state)
{
	char *delims[] = {" ", "\t", NULL};
	tk_info_t **tokens = NULL;
	char *alias_value = NULL;
	int i = 0;

	state->args = malloc(sizeof(char *) * BUFF_SIZE);

	tokens = tokenize(input, delims);

	/*handling aliass*/
	alias_value = (char *)_get_value(state->alias_head, tokens[0]->str);
	if (alias_value)
	{
		tk_info_t **alias_tokens;

		alias_value = strdup(alias_value);
		alias_tokens = tokenize(alias_value, delims);
		i = 0;
		while (alias_tokens[i])
		{
			state->args[i] = strdup(alias_tokens[i]->str);
			++i;
		}
		free(alias_value);
		_free_token_info_array(alias_tokens);
	}

	while (tokens[i])
	{
		state->args[i] = strdup(tokens[i]->str);
		++i;
	}
	state->args[i] = NULL;
	_handle_variables(state);
	_free_token_info_array(tokens);
	return (state->args);
}
/**
 * _cut_comments - cut comments off the input
 * @input: input string
 */
void _cut_comments(char *input)
{
	while (*input != '\0')
	{
		if (*input == '#')
		{
			*input = '\0';
			return;
		}
		++input;
	}
}
/**
 * _free_args - free args array
 * @args: args
 */
void _free_args(char **args)
{
	int i = 0;

	while (args[i])
	{
		free(args[i]);
		++i;
	}
	free(args);
}
/**
 * _handle_variables - make a sub to var value if exist
 * @state: state of the shell
 */
void _handle_variables(state_t *state)
{
	int k = 0;

	while (state->args[k])
	{
		if (strcmp(state->args[k], "$?") == 0)
		{
			free(state->args[k]);
			state->args[k] = int_to_str(state->last_cmd_status);
		}
		else if (strcmp(state->args[k], "$$") == 0)
		{
			free(state->args[k]);
			state->args[k] = int_to_str(state->pid);
		}
		else
		{
			if (state->args[k][0] == '$')
			{
				const char *value = NULL;

				value = _get_value(state->env_head, state->args[k] + 1);
				if (value)
				{
					free(state->args[k]);
					state->args[k] = strdup(value);
				}
				else
				{
					free(state->args[k]);
					state->args[k] = strdup("");
				}

			}
		}
#ifdef DEBUG
		printf("%s\n", state->args[k]);
#endif
		++k;
	}
}
