#include "shell.h"

/**
  * @commands: String of commnands
 */
int handle_enter(char **commands)
{
	if (commands[0] == NULL || _strcmp(commands[0], "\n") == 0)
		return (1);

	return (0);
}
