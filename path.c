#include "shell.h"

/**
 * _is_path - if @filename a full path
 * @filename: a file name
 * Return: 1 if filenaem is a full path 0, if not.
 */
int _is_path(char *filename)
{
	return (strchr(filename, '/') == NULL ? 0 : 1);
}

/**
 * _get_path - return a malloc allocated cpy of PATH
 * @env: the environ array
 * Return: return cpy of the PATH var
 */
char *_get_path(char **env)
{
	while (*env != NULL)
	{
		if ((*env)[0] == 'P' && (*env)[1] == 'A')
			if ((*env)[2] == 'T' && (*env)[3] == 'H')
				if (*(env)[4] == '=')
					return (strdup(*env));
		++env;
	}
	return (NULL);
}

/**
 * _program_path - searches for the dir that hold a given program filename
 * @filename: name of the program
 * @env: the env array
 *
 * Return: the full path if the search succeeed or NULL.
 */
char *_program_path(char *filename, entry_node_t *env)
{
	char *path = NULL;
	char *path_var = NULL;
	tk_info_t **dirs = NULL;
	char *delims[] = {":", NULL};
	int i = 0;
	DIR *dirstream;

	path_var = (char *)_get_value(env, "PATH");

	if (path_var == NULL)
		return (NULL);
	path_var = strdup(path_var);

	dirs = tokenize(path_var, delims);

	while (dirs[i] != NULL)
	{
		struct dirent *dir = NULL;

		dirstream = opendir(dirs[i]->str);
		while ((dir = readdir(dirstream)))
		{
			if (strcmp(dir->d_name, filename) == 0)
			{
				path = malloc(sizeof(dirs[i]->str) + sizeof(filename) + 2);
				path[0] = '\0';
				strcat(path, dirs[i]->str);
				strcat(path, "/");
				strcat(path, filename);

				closedir(dirstream);
				_free_token_info_array(dirs), free(path_var);
				return (path);
			}
		}
		closedir(dirstream), ++i;
	}
	_free_token_info_array(dirs), free(path_var);
	return (NULL);
}
