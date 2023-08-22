#include "shell.h"

/**
 * _print_cursor - print the cursor
 */
void _print_cursor(void)
{
	write(STDOUT_FILENO, "o-///-> ", 8);
}
