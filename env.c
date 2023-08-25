include "shell.h"

/**
 * env_copy - make the shell environment from the environment passed to main
 * @environ: environment passed to main
 *
 * Return: pointer to the new environment
 */
char **env_copy(char **environ)
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
 * env_free - free the shell's environment
 * @environ: shell's environment
 *
 * Return: void
 */
void env_free(char **environ)
{
	unsigned int i;

	for (i = 0; environ[i] != NULL; i++)
		free(environ[i]);
	free(environ);
}

/**
 * env_plus - create a new environment variable
 * @shell_vars: pointer to struct of variables
 *
 * Return: void
 */
void env_plus(shell_t *shell_vars)
{
	unsigned int i;
	char **new;

	for (i = 0; shell_vars->env_vars[i] != NULL; i++)
		;
	new = malloc(sizeof(char *) * (i + 2));
	if (new == NULL)
	{
		print_error(shell_vars, NULL);
		shell_vars->status = 127;
		_close(shell_vars);
	}
	for (i = 0; shell_vars->env_vars[i] != NULL; i++)
		new[i] = shell_vars->env_vars[i];
	new[i] = new_env(shell_vars->tokens[1], shell_vars->tokens[2]);
	if (new[i] == NULL)
	{
		print_error(shell_vars, NULL);
		free(shell_vars->cmd_mem);
		free(shell_vars->commands);
		free(shell_vars->tokens);
		env_free(shell_vars->env_vars);
		free(new);
		exit(127);
	}
	new[i + 1] = NULL;
	free(shell_vars->env_vars);
	shell_vars->env_vars = new;
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
 * new_env - create a new environment variable string
 * @key: variable name
 * @value: variable value
 *
 * Return: pointer to the new string;
 */
char *new_env(char *key, char *value)
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
