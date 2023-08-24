#include "shell.h"

/**
 * is_a_match - checks for character matches  in a string
 * @c: character to be checked
 * @str: string to checked
 *
 * Return: 1 if identical else 0
 */
unsigned int is_a_match(char c, const char *str)
{
	unsigned int i = 0;

	for (; str[i] != '\0'; i++)
	{
		if (c == str[i])
			return (1);
	}
	return (0);
}

/**
 * custom_strtok - custom strtok
 * @str: string to tokenize
 * @delim: character to be used as delimiter
 *
 * Return: pointer to the next token or NULL
 */
char *custom_strtok(char *str, const char *delim)
{	
	/* token represent the current token */
	static char *token;
	static char *next_token;
	unsigned int i = 0;

	if (str)
		next_token = str;
	token = next_token;
	if (!token)
		return (NULL);

	/* find the first non-delim char */
	for (; next_token[i] != '\0'; i++)
	{
		if (is_a_match(next_token[i], delim) == 0)
			break;
	}
	/* search for null terminitor or '#' */
	if (next_token[i] == '\0' || next_token[i] == '#')
	{
		next_token = NULL;
		return (NULL);
	}
	/* set token to non-delim char (will be useful in next for-loop */
	token = next_token + i;
	next_token = token;

	/* find the next delim char */
	for (i = 0; next_token[i] != '\0'; i++)
	{
		if (is_a_match(next_token[i], delim) == 1)
			break;
	}
	if (next_token[i] == '\0')
		next_token = NULL;
	else
	{	
		/* replace delim char with '\0' */
		next_token[i] = '\0';
		next_token +=  i + 1;
		/* set next token to NULL if we are at the end of the string */
		if (*next_token == '\0')
			next_token = NULL;
	}
	return (token);
}
