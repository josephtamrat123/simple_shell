#include "shell.h"

/**
  * @name: String to be validated
 *
 */
int validate_env_name(char *name)
{
	if (name == NULL)
	{
		print_builtin_error("setenv: Needs 2 args", "");
		return (-1);
	}

	if (!is_valid_env_var_name(name))
	{
		print_builtin_error("setenv: Invalid name ", name);
		return (-1);
	}

	return (0);
}

/**
  * @name: String to be checked
 *
 */
int is_valid_env_var_name(char *name)
{
	int i;
	/* Verify that name is a valid env_var name (without "=") */
	for (i = 0; name[i] != '\0'; i++)
		if (name[i] == '=')
			return (0);

	return (1);
}

/**
  * @name: Name to be searched
 *
 */
int get_env_index(char *name)
{
	int i;
	int len = _strlen(name);

	for (i = 0; __environ[i] != NULL; i++)
		if (_strncmp(__environ[i], name, len) == 0)
			return (i);

	return (-1);
}
