#include "shell.h"

/**
  * @msg: Message to print as error
*/
void dispatch_error(char *msg)
{
 	perror(msg);
	 
	exit(errno);
	/*exit(127); */
}

/**
  * @msg: Error message
 * @arg: Argument passed to builtin
*/
void print_builtin_error(char *msg, char *arg)
{
	int len = _strlen(msg);
	char *first_av = get_first_av();

	write(STDERR_FILENO, first_av, _strlen(first_av));
	write(STDERR_FILENO, ": 1: ", 5);
	write(STDERR_FILENO, msg, len);
	write(STDERR_FILENO, arg, _strlen(arg));
	write(STDERR_FILENO, "\n", 1);
	set_process_exit_code(2);
}
