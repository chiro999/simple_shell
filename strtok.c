#include "shell.h"

/**
 * matching - checks if a character matches any in a string
 * @c: character to check
 * @str: string to check
 *
 * Return: 1 if match, 0 if not
 */
unsigned int matching(char c, const char *str)
{
	unsigned int i;

	for (i = 0; str[i] != '\0'; i++)
	{
		if (c == str[i])
			return (1);
	}
	return (0);
}

/**
 * _strtok - custom strtok
 * @str: string to tokenize
 * @delim: delimiter to tokenize against
 *
 * Return: pointer to the next token or NULL
 */
char *_strtok(char *str, const char *delim)
{
	static char *token;
	static char *next;
	unsigned int i;

	if (str != NULL)
		next = str;
	token = next;
	if (token == NULL)
		return (NULL);
	for (i = 0; next[i] != '\0'; i++)
	{
		if (matching(next[i], delim) == 0)
			break;
	}
	if (next[i] == '\0' || next[i] == '#')
	{
		next = NULL;
		return (NULL);
	}
	token = next + i;
	next = token;
	for (i = 0; next[i] != '\0'; i++)
	{
		if (matching(next[i], delim) == 1)
			break;
	}
	if (next[i] == '\0')
		next = NULL;
	else
	{
		next[i] = '\0';
		next = next + i + 1;
		if (*next == '\0')
			next = NULL;
	}
	return (token);
}
