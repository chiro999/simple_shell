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
    size_t i = 0;

    /* Count the number of environment variables */
    while (environ[i])
        i++;

    /* Allocate memory for the new environment array (+1 for the null terminator) */
    new = malloc(sizeof(char *) * (i + 1));
    if (!new)
    {
        perror("Fatal Error");
        exit(1);
    }

    i = 0;
    /* Replicate each environment variable and store in the new environment array */
    while (environ[i])
    {
        new[i] = _strdup(environ[i]);
        i++;
    }
    new[i] = NULL;

    /* Return the new environment array */
    return new;
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
	unsigned int i = 0;
	char **new;

	/* Count existing env vars */
	while (shell_vars->env_vars[i])
	{
		i++;
	}

	/* Malloc and +2 for new variable '/' */
	new = malloc(sizeof(char *) * (i + 2));

	/* Print error and set error status */
	if (!new)
	{
		print_error(shell_vars, NULL);
		shell_vars->status = 127;
		_close(shell_vars);
	}

	/* Copy env vars to new */
	i = 0;
	while (shell_vars->env_vars[i])
	{
		new[i] = shell_vars->env_vars[i];
		i++;
	}

	/* Create a new env var and store it in new */
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

	/* Null terminate new env and update old env with new env */
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
		for (j = 0; j < path_len; j++)
			if (path[j] != env[i][j])
				break;
		/* if they match in length and the next char after name is '=' */
		if (j == path_len && env[i][j] == '=')
			/* return env variable */
			return (&env[i]);
	}
	/* null env var if not found */
	return (NULL);
}

/**
 * new_env -  new environment var string
 * @key: env var name
 * @value: env var value
 *
 * Return: pointer to the new string;
 */
char *new_env(char *key, char *value)
{
	unsigned int key_len, val_len, i = 0, j = 0;
	char *new;

	key_len = _strlen(key);
	val_len = _strlen(value);

	/* +2 for '=' and '/' */
	new = malloc(sizeof(char) * (key_len + val_len + 2));
	if (!new)
		return NULL;

	while (key[i] != '\0')
	{
		new[i] = key[i];
		i++;
	}
	/* place '=' after key */
	new[i] = '=';

	while (value[j] != '\0')
	{
		new[i + 1 + j] = value[j];
		j++;
	}
	new[i + 1 + j] = '\0';

	return new;
}
