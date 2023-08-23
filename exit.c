#include "shell.h"

/**
 * _exit_ - Exit program
 * @inputs: variables
 * Return: void
 */
void _exit_(input_t *inputs)
{
	int status;

	if (_strncmp(inputs->tokens[0], "exit") == 0 &&
	    inputs->tokens[1] != NULL)
	{
		status = _atoi(inputs->tokens[1]);
		if (status == -1)
		{
			inputs->status = 2;
			_error(inputs, ": Illegal number: ");
			_printer(inputs->tokens[1]);
			_printer("\n");
			free(inputs->commands);
			inputs->commands = NULL;
			return;
		}
		inputs->status = status;
	}
	free(inputs->buffer);
	free(inputs->tokens);
	free(inputs->commands);
	free_environ(inputs->env);
	exit(inputs->status);
}
