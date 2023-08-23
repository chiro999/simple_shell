#include "shell.h"

/**
 * _builtins - checks if the command is a builtin
 * @inputs: variables
 * Return: pointer to the function or NULL
 */
void (*_builtins(input_t *inputs))(input_t *inputs)
{
	unsigned int i;
	builtins_t check[] = {
		{"exit", _exit_},
		{"env", _env},
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
		check[i].f(inputs);
	return (check[i].f);
}


/**
 * _env - prints the current environment
 * @inputs: struct of variables
 * Return: void.
 */
void _env(input_t *inputs)
{
	unsigned int i;

	for (i = 0; inputs->env[i]; i++)
	{
		_puts(inputs->env[i]);
		_puts("\n");
	}
	inputs->status = 0;
}

/**
 * _setenv - create a new environment variable, or edit an existing variable
 * @inputs: pointer to struct of variables
 *
 * Return: void
 */
void _setenv(input_t *inputs)
{
	char **env;
	char *input;

	if (inputs->tokens[1] == NULL || inputs->tokens[2] == NULL)
	{
		_error(inputs, ": Incorrect number of arguments\n");
		inputs->status = 2;
		return;
	}
	env = find_env(inputs->env, inputs->tokens[1]);
	if (env == NULL)
		add_env(inputs);
	else
	{
		input = add_value(inputs->tokens[1], inputs->tokens[2]);
		if (input == NULL)
		{
			_error(inputs, NULL);
			free(inputs->buffer);
			free(inputs->commands);
			free(inputs->tokens);
			free_environ(inputs->env);
			exit(127);
		}
		free(*env);
		*env = input;
	}
	inputs->status = 0;
}

/**
 * _unsetenv - remove an environment variable
 * @inputs: pointer to a struct of variables
 *
 * Return: void
 */
void _unsetenv(input_t *inputs)
{
	char **env, **new;

	unsigned int i, j;

	if (inputs->tokens[1] == NULL)
	{
		_error(inputs, ": Incorrect number of arguments\n");
		inputs->status = 2;
		return;
	}
	env = find_env(inputs->env, inputs->tokens[1]);
	if (env == NULL)
	{
		_error(inputs, ": No variable to unset");
		return;
	}
	for (i = 0; inputs->env[i] != NULL; i++)
		;
	new = malloc(sizeof(char *) * i);
	if (new == NULL)
	{
		_error(inputs, NULL);
		inputs->status = 127;
		_exit_(inputs);
	}
	for (i = 0; inputs->env[i] != *env; i++)
		new[i] = inputs->env[i];
	for (j = i + 1; inputs->env[j] != NULL; j++, i++)
		new[i] = inputs->env[j];
	new[i] = NULL;
	free(*env);
	free(inputs->env);
	inputs->env = new;
	inputs->status = 0;
}
