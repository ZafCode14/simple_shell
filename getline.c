#include "shell.h"

/**
 * _getline - getline function cpy
 * @lineptr: ptr to cmd
 * @n: size of lineptr
 * @fd: file descriptor
 *
 * Return: same as the original getline()
 */
ssize_t _getline(char **lineptr, size_t *n, int fd)
{
	static char buf[BUFF_SIZE];
	static size_t r_buf, s_buf;
	int nl_found = 0;
	ssize_t rflag, i_line = 0, s_line = 0;

	if (*lineptr == NULL)
	{
		s_line = BUFF_SIZE, *lineptr = malloc(s_line);
		memset(*lineptr, 0, s_line), *n = s_line;
	}
	while (!nl_found)
	{
		if (r_buf == s_buf)
		{
			if (s_buf == BUFF_SIZE)
			{
				s_buf = 0;
				r_buf = 0;
			}
			rflag = read(fd, buf + s_buf, BUFF_SIZE - s_buf);

			if (rflag > 0)
				s_buf += (size_t)rflag;
			else
				return (-1);
		}
		while (r_buf != s_buf)
		{
			if (i_line + 1 > s_line)
				s_line *= 2, *n = s_line, *lineptr = realloc(*lineptr, s_line);
			(*lineptr)[i_line] = buf[r_buf], ++i_line, ++r_buf;
			if (buf[r_buf - 1] == '\n')
			{
				(*lineptr)[i_line] = '\0', nl_found = 1;
				break;
			}
		}
	}
	return (i_line);
}
