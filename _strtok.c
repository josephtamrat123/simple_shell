#include "shell.h"

 static char *TKN_PTR = "";
static int NO_INIT_TKN_PTR = 1;

 int isdelimiter(char c, char *delimiter);

/**
  * @str: String to be divided
 * @delimiter: Delimiter by which to str will be divided
 *
 */
char *_strtok(char *str, char *delimiter)
{
	char *curr_pos;
	char *tkn_start = NULL;

	if (NO_INIT_TKN_PTR == 1)
	{
		TKN_PTR = NULL;
		NO_INIT_TKN_PTR = 0;
	}

	if ((str == NULL && TKN_PTR == NULL) || (str != NULL && str[0] == '\0'))
		return (NULL);

	if (str != NULL)
		TKN_PTR = str;

	for (curr_pos = TKN_PTR; *curr_pos != '\0'; curr_pos++)
	{
		if (!isdelimiter(*curr_pos, delimiter))
		{
			tkn_start = curr_pos;
			while (*curr_pos != '\0' && !isdelimiter(*curr_pos, delimiter))
				curr_pos++;

			TKN_PTR = curr_pos + 1;
			if (*curr_pos == '\0')
				TKN_PTR = curr_pos;
			*curr_pos = '\0';

			return (tkn_start);
		}
	}

	return (NULL);
}

/**
  * @c: Char to evaluate
 * @delimiter: Set of chars as delimiters
 *
 */
int isdelimiter(char c, char *delimiter)
{
	while (*delimiter != '\0')
	{
		if (c == *delimiter)
			return (1);
		delimiter++;
	}

	return (0);
}
