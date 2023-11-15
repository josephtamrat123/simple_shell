#include "shell.h"

 
void env(void)
{
	int i;
	char **env = __environ;

	for (i = 0; env[i]; i++)
	{
		write(STDOUT_FILENO, env[i], _strlen(env[i]));
		write(STDOUT_FILENO, "\n", 1);
	}

	set_process_exit_code(0);
}

/**
  * @name: Name for the new env variable
 * @value: Value for the new env variable
 *
  */
int _setenv(char *name, char *value)
{
	int env_index, new_var_len;

	if (validate_env_name(name) == -1)
		return (-1);

	env_index = get_env_index(name);
	if (env_index == -1)
	{/* var doen't exist, SO CREATE IT */
		int env_count = 0;
		int old_size, new_size;

		while (__environ[env_count] != NULL)
			env_count++;

		old_size = sizeof(char *) * (env_count);
		new_size = sizeof(char *) * (env_count + 2);
		__environ = _realloc(__environ, old_size, new_size);
		if (__environ == NULL)
			dispatch_error("Error while _reallocating memory for new env var");

 		env_index = env_count;
 		__environ[env_count + 1] = NULL;
	}
	else
	{
 		free(__environ[env_index]);
	}

	new_var_len = _strlen(name) + _strlen(value) + 2;
 	__environ[env_index] = allocate_memory(sizeof(char) * new_var_len);
	_strcpy(__environ[env_index], name);
	_strcat(__environ[env_index], "=");
	_strcat(__environ[env_index], value);

	set_process_exit_code(0);
	return (1);
}

/**
  * @name: Name for the new env variable
 *
 * Return: 1 on success, -1 on error
 */
int _unsetenv(char *name)
{
	int env_index, i;

	env_index = get_env_index(name);
	if (env_index >= 0)
	{/* var exists, We can unset it */
		free(__environ[env_index]);

		for (i = env_index; __environ[i] != NULL; i++)
			__environ[i] = __environ[i + 1];

		set_process_exit_code(0);
		return (1);
	}

 	set_process_exit_code(0); /* Indicates that no error ocurred */

	return (1);
}

/**
  * @path: Path to wich change the working directory
 *
 */
int _cd(char *path)
{
	char buff[1024];
	char *oldpwd;
	char *_path = path;

	if (_strcmp(path, "-") == 0)
		path = _getenv("OLDPWD");

	if (path == NULL)
	{
		print_builtin_error("cd: OLDPWD not set", "");
		return (-1);
	}
 	path = duplicate_string(path);
 	oldpwd = getcwd(buff, 1024);
	if (oldpwd == NULL)
	{
		free(path);
		print_builtin_error("cd: couldn't get current dir", "");
		return (-1);
	}
 	if (chdir(path) == -1)
	{
		free(path);
		print_builtin_error("cd: can't change cd to ", _path);
		set_process_exit_code(1);
		return (-1);
	}
	/* Update env variables */
	_setenv("OLDPWD", oldpwd);
	_setenv("PWD", path);
	free(path);
	set_process_exit_code(0);
	return (1);
}

/**
  * @commands: List of commands
 *
 */
int _alias(char **commands)
{
	int status = 0;
	list_t *curr;
	list_t *out_head = NULL;
	list_t **alias_addrs = get_alias_head();

 	if (commands[1] == NULL)
	{ /* This means to list all the aliases */
		for (curr = *alias_addrs; curr != NULL; curr = curr->next)
		{
			_puts(curr->str);
			_puts("\n");
		}
		set_process_exit_code(0);
		return (1);
	}
 	status = handle_alias_args(commands, &out_head);
 	for (curr = out_head; curr != NULL; curr = curr->next)
	{
		_puts(curr->str);
		_puts("\n");
	}
	/* free list */
	free_list(out_head);
	return (status);
}
