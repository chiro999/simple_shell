#include "shell.h"

/**
 * init_env - make the shell environment from the environment passed to main
 * @environ: environment passed to main
 *
 * Return: pointer to the new environment
 */
char **init_env(char **environ)
{
	char **new = NULL;
	size_t i;

	for (i = 0; environ[i] != NULL; i++)
		;
	new = malloc(sizeof(char *) * (i + 1));
	if (new == NULL)
	{
		perror("Fatal Error");
		exit(1);
	}
	for (i = 0; environ[i] != NULL; i++)
		new[i] = _strdup(environ[i]);
	new[i] = NULL;
	return (new);
}

/**
 * free_environ - free the shell's environment
 * @environ: shell's environment
 *
 * Return: void
 */
void free_environ(char **environ)
{
	unsigned int i;

	for (i = 0; environ[i] != NULL; i++)
		free(environ[i]);
	free(environ);
}

/**
 * add_env - create a new environment variable
 * @inputs: pointer to struct of variables
 *
 * Return: void
 */
void add_env(input_t *inputs)
{
	unsigned int i;
	char **new;

	for (i = 0; inputs->env[i] != NULL; i++)
		;
	new = malloc(sizeof(char *) * (i + 2));
	if (new == NULL)
	{
		_error(inputs, NULL);
		inputs->status = 127;
		_exit_(inputs);
	}
	for (i = 0; inputs->env[i] != NULL; i++)
		new[i] = inputs->env[i];
	new[i] = add_value(inputs->tokens[1], inputs->tokens[2]);
	if (new[i] == NULL)
	{
		_error(inputs, NULL);
		free(inputs->buffer);
		free(inputs->commands);
		free(inputs->tokens);
		free_environ(inputs->env);
		free(new);
		exit(127);
	}
	new[i + 1] = NULL;
	free(inputs->env);
	inputs->env = new;
}

/**
 * find_env - finds an environment variable
 * @env: array of environment variables
 * @path: environment variable to find
 *
 * Return: pointer to address of the environment variable
 */
char **find_env(char **env, char *path)
{
	unsigned int i, j, len;

	len = _strlen(path);
	for (i = 0; env[i] != NULL; i++)
	{
		for (j = 0; j < len; j++)
			if (path[j] != env[i][j])
				break;
		if (j == len && env[i][j] == '=')
			return (&env[i]);
	}
	return (NULL);
}

/**
 * add_value - create a new environment variable string
 * @key: variable name
 * @value: variable value
 *
 * Return: pointer to the new string;
 */
char *add_value(char *key, char *value)
{
	unsigned int len1, len2, i, j;
	char *new;


	len1 = _strlen(key);
	len2 = _strlen(value);
	new = malloc(sizeof(char) * (len1 + len2 + 2));
	if (new == NULL)
		return (NULL);
	for (i = 0; key[i] != '\0'; i++)
		new[i] = key[i];
	new[i] = '=';
	for (j = 0; value[j] != '\0'; j++)
		new[i + 1 + j] = value[j];
	new[i + 1 + j] = '\0';
	return (new);
}
