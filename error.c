#include "shell.h"

/**
 * _error - prints error messages to standard error
 * @inputs: pointer to struct of variables
 * @message: message to print
 *
 * Return: void
 */
void _error(input_t *inputs, char *message)
{
	char *count;

	_printer(inputs->argv[0]);
	_printer(": ");
	count = _int_str(inputs->count);
	_printer(count);
	free(count);
	_printer(": ");
	_printer(inputs->tokens[0]);
	if (message)
	{
		_printer(message);
	}
	else
		perror("");
}
