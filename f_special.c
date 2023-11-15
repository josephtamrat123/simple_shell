#include "shell.h"

/**
 * build_dynamic_environ -  
*/
void build_dynamic_environ(void)
{
	int count_envs = 0;
	char **new_environ;

	while (__environ[count_envs] != NULL)
		count_envs++;

	new_environ = allocate_memory(sizeof(char *) * (count_envs + 1));
	for (count_envs = 0;  __environ[count_envs] != NULL; count_envs++)
		new_environ[count_envs] = duplicate_string(__environ[count_envs]);

 	new_environ[count_envs] = NULL;
 	__environ = new_environ;
}

/**
 * free_dynamic_environ -  
 */
void free_dynamic_environ(void)
{
	free_dbl_ptr(__environ);
}
