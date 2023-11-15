#include "shell.h"

/**
  * @buff: User's input
 * @cmds_list: Array of parsed commands
 * @commands: User's input parsed as array of commands
 *
 */
int handle_exit(char *buff, char **cmds_list, char **commands)
{
	int status;

 	if (commands[0] == NULL || _strcmp(commands[0], "exit") != 0)
		return (0);

 	if (commands[1] == NULL)
	{
		write_history();
		free_allocs(buff, cmds_list, commands, F_BUFF | F_CMDS);
		if (*process_exit_code() == 127)
			exit(2);
		exit(0);
	}

	status = get_exit_status(commands[1]);
 	if (status >= 0)
	{
		write_history();
		free_allocs(buff, cmds_list, commands, F_BUFF | F_CMDS);
		exit(status);
	}

 	print_builtin_error("exit: Illegal number: ", commands[1]);
	return (-1);
}

/**
  * @buff: User's input
 *
 */
int get_exit_status(char *buff)
{
	int i;
	int status = 0;

	for (i = 0; buff[i] != '\0'; i++)
	{
		if (buff[i] == '\n')
			return (status);

		if (buff[i] < '0' || buff[i] > '9')
			return (-1);

		status *= 10;
		status += buff[i] - '0';
	}

	return (status);
}
