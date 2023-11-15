#include "shell.h"

/* Global variables */
static int no_init_history;
static list_t *history_head;
static list_t *last_cmd;

 
list_t **get_history_addrss()
{
	if (no_init_history == 1)
	{
		history_head = NULL;
		last_cmd = NULL;
		no_init_history = 0;
	}

	return (&history_head);
}

/**
 * get_last_cmd_addrss - Return the address oof history head
 *
 */
list_t **get_last_cmd_addrss()
{
	if (no_init_history == 1)
	{
		history_head = NULL;
		last_cmd = NULL;
		no_init_history = 0;
	}

	return (&last_cmd);
}

/**
 * _history - Prints the all the commands entered by the user
 *
 */
int _history(void)
{
	list_t *curr;
	char *str_num;
	int i, len;
	int count = *get_history_lines_count() % 4096;

	for (curr = *get_history_addrss(); curr != NULL; curr = curr->next)
	{
		str_num = num_to_str(count++);
		len = _puts(str_num);
		for (i = len; i < 7; i++) /* 5 per number, 2 aditional */
			_puts(" ");
		_puts(curr->str);
		_puts("\n");
		free(str_num);
	}

	return (1);
}

/**
  * @buff: User's input
*/
void handle_history(char *buff)
{
	/* Only adds a command if is different from the previous one */
	if (last_cmd == NULL || buff[0] != ' ' || _strcmp(last_cmd->str, buff) != 0)
		last_cmd = add_node_end(get_history_addrss(), buff);
}

/**
 */
void free_history(void)
{
	free_list(*get_history_addrss());
}
