#ifndef _TOKEN_H_
#define _TOKEN_H_

#define DELIM(n) (1u << n)

/**
 * struct tk_info - a struct that represent a token
 * @str: str token
 * @flags: itch bit if up represent a delim incountered
 */
typedef struct tk_info
{
	char *str;
	unsigned int flags;
} tk_info_t;

tk_info_t **tokenize(char *input, char **delims);
void _free_token_info_array(tk_info_t **);

/*
 * The tokenize function can only take up to 63 delims
 * cus the way we flage an encounted demis is by raising a flag
 * and uint is represented in 64 bits only.
 *
 * tokenize() modifies the input string so be carefull using it.
 */
#endif
