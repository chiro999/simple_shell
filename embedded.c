#include "shell.h"

/**
 * _embedded - checks if the command is an embedded function
 * @shell_vars: variables
 * Return: the function or NULL
 */
void (*_embedded(shell_t *shell_vars))(shell_t *shell_vars)
{
	unsigned int i = 0;
	embedded_t selector[] = {
		{"exit", _close},
		{"env", curr_env},
		{"setenv", _setenv},
		{"unsetenv", _unsetenv},
		{NULL, NULL}
	};
	
	/* function selector, compares input command with the commands above  */
	for (; selector[i].f != NULL; i++)
	{	
		if (_strcmp(shell_vars->tokens[0], selector[i].name) == 0)
			break;
	}
	if (selector[i].f)
		selector[i].f(shell_vars);
	return (selector[i].f);
}


/**
 * curr_env - prints the current environment
 * @shell_vars:  variables
 * Return: void.
 */
void curr_env(shell_t *shell_vars)
{
	unsigned int i = 0;

	for (; shell_vars->env_vars[i]; i++)
	{
		str_out(shell_vars->env_vars[i]);
		str_out("\n");
	}
	shell_vars->status = 0;
}

/**
 * _setenv - create or environment variables
 * @shell_vars: struct of variables
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
	env = find_env(shell_vars->env_vars, shell_vars->tokens[1]);
	if (!env)
		env_plus(shell_vars);
	else
	{
		input = new_env(shell_vars->tokens[1], shell_vars->tokens[2]);
		if (!input)
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
 * _unsetenv - removes an environment variable
 * @shell_vars:  struct of variables
 *
 * Return: void
 */
void _unsetenv(shell_t *shell_vars)
{
	char **env, **new;

	unsigned int i = 0;
        unsigned int j;

	if (!(shell_vars->tokens[1]))
	{
		print_error(shell_vars, ": Incorrect number of arguments\n");
		shell_vars->status = 2;
		return;
	}
	env = find_env(shell_vars->env_vars, shell_vars->tokens[1]);
	if (!env)
	{
		print_error(shell_vars, ": No variable to unset");
		return;
	}
	for (; shell_vars->env_vars[i] != NULL; i++)
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
	shell_vars->env_vars = new;
	shell_vars->status = 0;
}
