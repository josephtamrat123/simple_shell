#include "shell.h"

/**
  * @str: String to be printed
 *
 */
int _puts(char *str)
{
	int len = _strlen(str);

	write(STDOUT_FILENO, str, len);

	return (len);
}
