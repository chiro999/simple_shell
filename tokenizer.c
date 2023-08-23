#include "shell.h"

/**
 * custom_tokenizer - tokenizes a buffer with a delimiter
 * @arguments: buffer to tokenize
 * @delimiter: delimiter to tokenize along
 *
 * Return: pointer to an array of pointers to the tokens
 */
char **custom_tokenizer(char *arguments, char *delimiter)
{
	char **tokens = NULL;
	size_t i = 0, count = 10;

	if (arguments == NULL)
		return (NULL);
	tokens = malloc(sizeof(char *) * count);
	if (tokens == NULL)
	{
		perror("Fatal Error");
		return (NULL);
	}
	while ((tokens[i] = custom_strtok(arguments, delimiter)) != NULL)
	{
		i++;
		if (i == count)
		{
			tokens = _realloc(tokens, &count);
			if (tokens == NULL)
			{
				perror("Fatal Error");
				return (NULL);
			}
		}
		arguments = NULL;
	}
	return (tokens);
}
