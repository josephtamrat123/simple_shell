#include "shell.h"

/**
  * @str_input: Command input given by the user
 * @delimiter: String od chars indicating the delimiters
 *
 */
char **parse_user_input(char *str_input, char *delimiter)
{
	int i, args_count = 0;
	char **args;
	char *token, *tkn_ptr;
	char *str_copy;

	if (str_input == NULL)
		dispatch_error("Error while parsing the command\n");

 	args_count = count_args(str_input, delimiter);
 	args = allocate_memory(sizeof(char *) * (args_count + 1));
 	str_copy = duplicate_string(str_input);
	tkn_ptr = str_copy;
	for (i = 0; i < args_count; i++)
	{
		token = _strtok(tkn_ptr, delimiter);
		if (token == NULL)
			break;
		tkn_ptr = NULL;
 		args[i] = duplicate_string(token);
	}
 	args[i] = NULL;

	free(str_copy);

	return (args);
}

/**
  * @str_input: Command as a string
 * @delimiter: Delimiter by wich to separate the args
 *
 */
int count_args(char *str_input, char *delimiter)
{
	char *tkn, *tkn_ptr;
	int count = 0;
	char *str_copy = duplicate_string(str_input);

	tkn_ptr = str_copy;
	while ((tkn = _strtok(tkn_ptr, delimiter)) != NULL)
	{
		count++;
		tkn_ptr = NULL;
	}

	free(str_copy);

	return (count);
}

/**
  * @commands: Array of strings containing the command and args
 */
int handle_PATH(char **commands)
{
	char *path_dirs, *path;
	char *tkn, *tkn_ptr;
	char *str_copy;
	int flag = 127;

	if (
		commands == NULL || commands[0] == NULL ||
		commands[0][0] == '\0' || commands[0][0] == '/'
	)
		return (127);

	if (access(commands[0], F_OK) == 0)
		return (0);

	path_dirs = _getenv("PATH");
	if (path_dirs == NULL)
		return (127);

	str_copy = duplicate_string(path_dirs);
	tkn_ptr = str_copy;
	while (1)
	{
		tkn = _strtok(tkn_ptr, ":");
		if (tkn == NULL)
			break;
		tkn_ptr = NULL;
		path = getpath(tkn, commands[0]);
		if (access(path, F_OK) != -1)
		{
			free(commands[0]);
			commands[0] = path;
			flag = 0;
			break;
		}
		free(path);
	}
	free(str_copy);
	return (flag);
}

/**
  * @dir: String representing a directory path
 * @filename: Name of the file we are looking for
 *
 */
char *getpath(char *dir, char *filename)
{
	int dir_len = _strlen(dir);
	int filename_len = _strlen(filename);
	char *path;

	path = allocate_memory(sizeof(char *) * (dir_len + filename_len + 2));

	_strcpy(path, dir);
	_strcat(path, "/");
	_strncat(path, filename, filename_len + 1);

	return (path);
}
