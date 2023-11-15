#include "shell.h"

/**
 * @s: string 1
 * @c: character to search

 */
char *_strchr(const char *s, int c)
{
	size_t i;

	i = 0;
	while (s[i])
	{
		if (s[i] == c)
			return ((char *)&s[i]);
		i++;
	}
	if (c == '\0')
		return ((char *)(&s[i]));
	return (NULL);
}

/**
 * _strcat - concatenate two strings
 * @s1: string 1
 * @s2: string 2
 */
char *_strcat(char *s1, const char *s2)
{
	return (_strncat(s1, s2, -1));
}

/**
 * _strncat - concatenate first n chars of s2 to s1 string
 
 * @n: numbers of characters of s2 to concatenate to the s1
 */
char *_strncat(char *s1, const char *s2, size_t n)
{
	size_t i;
	size_t j;

	i = _strlen(s1);
	j = 0;
	while (s2[j] && j < n)
		s1[i++] = s2[j++];
	s1[i] = '\0';
	return (s1);
}
