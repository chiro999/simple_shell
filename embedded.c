#include "shell.h"

/**
 * _embedded - checks if the command is a builtin
 * @inputs: variables
 * Return: pointer to the function or NULL
 */
void (*_embedded(shell_t *shell_vars))(shell_t *shell_vars)
{
	unsigned int i;
	embedded_t check[] = {
		{"exit", _close},
		{"env", curr_env},
		{"setenv", _setenv},
		{"unsetenv", _unsetenv},
		{NULL, NULL}
	};

	for (i = 0; check[i].f != NULL; i++)
	{
		if (_strncmp(inputs->tokens[0], check[i].name) == 0)
			break;
	}
	if (check[i].f != NULL)
		check[i].f(shell_vars);
	return (check[i].f);
}


/**
 * curr_env - prints the current environment
 * @inputs: struct of variables
 * Return: void.
 */
void curr_env(shell_t *shell_vars)
{
	unsigned int i;

	for (i = 0; shell_vars->env_vars[i]; i++)
	{
		str_out(shell_vars->env_vars[i]);
		str_out("\n");
	}
	shell_vars->status = 0;
}

/**
 * _setenv - create a new environment variable, or edit an existing variable
 * @inputs: pointer to struct of variables
 *
 * Return: void
 */
void _setenv(shell_t *shell_vars)
{
	char **env;
	char *input;

	if (shell_vars->tokens[1] == NULL || shell_vars->tokens[2] == NULL)
	{
		print_error(shell_vars, ": Incorrect number of arguments\n");
		shell_vars->status = 2;
		return;
	}
	env = env_plus(shell_vars->env_vars, shell_vars->tokens[1]);
	if (env == NULL)
		env_plus(inputs);
	else
	{
		input = add_value(inputs->tokens[1], inputs->tokens[2]);
		if (input == NULL)
		{
			print_error(shell_vars, NULL);
			free(shell_vars->cmd_mem);
			free(shell_vars->commands);
			free(shell_vars->tokens);
			env_free(shell_vars->env_vars);
			exit(127);
		}
		free(*env);
		*env = input;
	}
	shell_vars->status = 0;
}

/**
 * _unsetenv - remove an environment variable
 * @inputs: pointer to a struct of variables
 *
 * Return: void
 */
void _unsetenv(shell_t *shell)
{
	char **env, **new;

	unsigned int i, j;

	if (shell_vars-tokens[1] == NULL)
	{
		print_error(shell_vars, ": Incorrect number of arguments\n");
		shell_vars->status = 2;
		return;
	}
	env = is_env(shell_vars->env_vars, shell_vars->tokens[1]);
	if (env == NULL)
	{
		print_error(shell_vars, ": No variable to unset");
		return;
	}
	for (i = 0; shell_vars->env_vars[i] != NULL; i++)
		;
	new = malloc(sizeof(char *) * i);
	if (new == NULL)
	{
		print_error(shell_vars, NULL);
		shell_vars->status = 127;
		_close(shell_vars);
	}
	for (i = 0; shell_vars->env_vars[i] != *env; i++)
		new[i] = shell_vars->env_vars[i];
	for (j = i + 1; shell_vars->env_vars[j] != NULL; j++, i++)
		new[i] = shell_vars->env_vars[j];
	new[i] = NULL;
	free(*env);
	free(shell_vars->env_vars);
	shell_vars->env = new;
	shell_vars->status = 0;
}
