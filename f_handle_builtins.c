#include "shell.h"

int envars_builtins(char **commands);
int other_set_buitlins(char **commands);

/**
  * @commands: User's input parsed as an array of commads
 */
int handle_builtins(char **commands)
{
	if (commands[0] == NULL)
		return (0);

	if (envars_builtins(commands))
		return (1);

	if (other_set_buitlins(commands))
		return (1);

	return (0);
}

/**
  * @commands: Arrays of commnads
 */
int envars_builtins(char **commands)
{
	if (_strcmp(commands[0], "env") == 0)
	{
		if (commands[1] != NULL)
			return (0);

		env();
		return (1);
	}

	if (_strcmp(commands[0], "setenv") == 0)
	{
		if (commands[1] == NULL || commands[2] == NULL || commands[3] != NULL)
			return (1);

		_setenv(commands[1], commands[2]);
		return (1);
	}

	if (_strcmp(commands[0], "unsetenv") == 0)
	{
		if (commands[1] == NULL || commands[2] != NULL)
			return (1);

		_unsetenv(commands[1]);
		return (1);
	}

	return (0);
}

/**
  * @commands: Arrays of commnads
 *
 */
int other_set_buitlins(char **commands)
{
	if (_strcmp(commands[0], "cd") == 0)
	{
		char *path = commands[1];

		if (commands[1] == NULL)
			path = _getenv("HOME");

		if (path == NULL)
			path = "/";

		_cd(path);
		return (1);
	}

	if (_strcmp(commands[0], "alias") == 0)
	{
		_alias(commands);
		return (1);
	}

	if (_strcmp(commands[0], "help") == 0)
	{
		_help(commands);
		return (1);
	}

	if (_strcmp(commands[0], "history") == 0)
	{
		if (commands[1] != NULL)
		{
			print_builtin_error("history: No args allowed", "");
			return (1);
		}

 		/*return (1);*/
	}

	return (0);
}
