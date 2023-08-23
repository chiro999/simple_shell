#include "shell.h"

/**
 * env_copy - create shell env from the env passed to main
 * @environ: env passed to main
 *
 * Return: new environment
 */
char **env_copy(char **environ)
{
	char **new = NULL;
	size_t i;
	/* number of env variables */
	for (i = 0; environ[i] != NULL; i++)
		;
	/* allocate memory + 1 for null terminator */
	new = malloc(sizeof(char *) * (i + 1));
	if (new == NULL)
	{
		perror("Fatal Error");
		exit(1);
	}
	/* replicate the env variables and store in new environment */
	for (i = 0; environ[i] != NULL; i++)
		new[i] = _strdup(environ[i]);
	new[i] = NULL;
	/* new environment */
	return (new);
}

/**
 * env_free - free shell env
 * @environ: shell env
 *
 * Return: void
 */
void env_free(char **environ)
{
	unsigned int i = 0;

	for (; environ[i] != NULL; i++)
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

	/* count existing env vars */
	for (i = 0; shell_vars->env_vars[i] != NULL; i++)
		;
	/* malloc and +2 for new variable '/' */
	new = malloc(sizeof(char *) * (i + 2));
	/* print error and set error status */
	if (!new)
	{
		print_error(shell_vars, NULL);
		shell_vars->status = 127;
		_close(shell_vars);
	}
	/* copy env vars to new */
	for (i = 0; shell_vars->env_vars[i] != NULL; i++)
		new[i] = shell_vars->env_vars[i];
	/* create a new env var and store it in new */
	new[i] = new_env(shell_vars->tokens[1], shell_vars->tokens[2]);
	if (!new[i])
	{
		print_error(shell_vars, NULL);
		free(shell_vars->cmd_mem);
		free(shell_vars->commands);
		free(shell_vars->tokens);
		env_free(shell_vars->env_vars);
		free(new);
		exit(127);
	}
	/* null terminate new env and update old env with new env */
	new[i + 1] = NULL;
	free(shell_vars->env_vars);
	shell_vars->env_vars = new;
}

/**
 * find_env - finds an env variable
 * @env: array of env variables
 * @path: specific env variable
 *
 * Return: pointer to address of the environment variable
 */
char **find_env(char **env, char *path)
{
	unsigned int i = 0, j, path_len;

	path_len = _strlen(path);
	for (; env[i] != NULL; i++)
	{	/* compare curr_env with target env */
		for (j = 0; j < len; j++)
			if (path[j] != env[i][j])
				break;
		/* if they match in length and the next char after name is '=' */
		if (j == len && env[i][j] == '=')
			/* return env variable */
			return (&env[i]);
	}
	/* null env var if not found */
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
	unsigned int key_len, val_len, i, j;
	char *new;


	key_len = _strlen(key);
	val_len = _strlen(value);
	/* +2 for '=' and '/' */
	new = malloc(sizeof(char) * (key_len + val_len + 2));
	if (!new)
		return (NULL);
	for (i = 0; key[i] != '\0'; i++)
		new[i] = key[i];
	new[i] = '=';
	for (j = 0; value[j] != '\0'; j++)
		new[i + 1 + j] = value[j];
	new[i + 1 + j] = '\0';
	return (new);
}
