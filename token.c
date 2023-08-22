#include "shell.h"

int _is_delim(char *input, char **delims);

/**
 * tokenize - tokenize an input
 * @input: input string
 * @delims: null-terminated array of the delims char *
 * Return: tk_info_t * arrays
 */
tk_info_t **tokenize(char *input, char **delims)
{
	tk_info_t **tokens = NULL;
	int i_tokens = 0, offset = 0;

	tokens = malloc(sizeof(tk_info_t *) * BUFF_SIZE);
	while (input[0] != '\0')
	{
		unsigned int flags = 0;

		offset = 0;
		while (input[0] != '\0')
		{
			int index =  _is_delim(input, delims);

			if (index != -1)
			{
#ifdef DBUG
				printf("->delim: %s\n", input);
#endif
				input[0] = '\0';
				input[strlen(delims[index]) - 1] = '\0';
				input += strlen(delims[index]);
				flags |= 1u << index;
			}
			else
			{
				break;
			}
		}
		while (input[offset] != '\0' && _is_delim(input + offset, delims) == -1)
		{
#ifdef DBUG
			printf("->no delim: %c\n", input[offset]);
#endif
			++offset;
		}
		if (offset)
		{
			tk_info_t *entry = malloc(sizeof(tk_info_t));

			entry->str = input;
			entry->flags = flags;

			tokens[i_tokens] = entry;
			++i_tokens;

			input += offset;
		}
	}
	tokens[i_tokens] = NULL;
	return (tokens);
}

/**
 * _is_delim - is one of the delim is present at the start of input
 * @input: input string
 * @delims: null-terminated array of the delims char *
 *
 * Description: is a helper function used in tokenize()
 * Return: the index of the delim found or -1
 */
int _is_delim(char *input, char **delims)
{
	int i = 0;

	while (delims[i])
	{
		if (strncmp(input, delims[i], strlen(delims[i])) == 0)
			return (i);
		++i;
	}
	return (-1);
}

/**
 * _free_token_info_array - free a array of tk_info_t *
 * @array: null-terminated array of allocated tk_info_t *
 */
void _free_token_info_array(tk_info_t **array)
{
	int i = 0;

	while (array[i])
	{
		free(array[i]);
		++i;
	}
	free(array);
}
