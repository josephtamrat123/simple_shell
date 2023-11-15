#include "shell.h"

/**
  * @bytes: Number representing the size in bytes to allocate
 
 */
void *allocate_memory(unsigned int bytes)
{
	char *new_mem = malloc(bytes);

	if (new_mem == NULL)
		dispatch_error("Error while allocating memory\n");

	return (new_mem);
}

/**
  * @str: String to dulicate
 */
char *duplicate_string(char *str)
{
	char *str_copy = _strdup(str);

	if (str_copy == NULL)
		dispatch_error("Error while making copy of string");

	return (str_copy);
}

/**
  * @dbl_ptr: Double pointer
*/
void free_dbl_ptr(char **dbl_ptr)
{
	int i;

	if (dbl_ptr == NULL)
		return;

	for (i = 0; dbl_ptr[i]; i++)
		free(dbl_ptr[i]);

	free(dbl_ptr);
}

/**
  * @buff: Main buffer
 * @cmds_list: List of commands
 * @commands: Command as an array of arguments
 * @flags: Number indicating which memory to free
*/
void free_allocs(char *buff, char **cmds_list, char **commands, int flags)
{
	if (flags & F_BUFF)
		free(buff);
	if (flags & F_CMD_L)
		free_dbl_ptr(cmds_list);
	if (flags & F_CMDS)
		free_dbl_ptr(commands);

	free_list(*(get_alias_head()));
	free_history();
}
