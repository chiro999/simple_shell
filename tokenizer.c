include "shell.h"

/**
 * custom_tokenizer - tokenizes args with a delimiter
 * @args: args to be tokenized
 * @delim: char to be used as delimiter
 *
 * Return: pointer to an array of pointers to the tokens
 */
char **custom_tokenizer(char *args, char *delim)
{
	char **tokens = NULL;
	size_t i = 0;
        size_t count = 10;

	if (!args)
		return (NULL);
	/* malloc for tokens */
	tokens = malloc(sizeof(char *) * count);
	/* malloc failure */
	if (!tokens)
	{
		perror("Fatal Error");
		return (NULL);
	}
	/* tokenize using custom_strtok */
	while ((tokens[i] = custom_strtok(args, delim)))
	{
		i++;
		/* if token has matched the size of the array */
		if (i == count)
		{	
			/* malloc using the more_mem function */
			tokens = more_mem(tokens, &count);
			/* malloc failure */
			if (!tokens)
			{
				perror("Fatal Error");
				return (NULL);
			}
		}
		args = NULL;
	}
	return (tokens);
}
