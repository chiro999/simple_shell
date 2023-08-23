#include "shell.h"

/**
 * print_error - prints error messages to standard error
 * @shell_vars: pointer to struct of variables
 * @err_message: message to print
 *
 * Return: void
 */
void pint_error(shell_t *shell_vars, char *err_message)
{
	char *tokenCount;

	str_error(shell_vars->argv[0]);
	str_error(": ");
	tokenCount = int_to_string(shell_vars->tokenCount);
	str_error(tokenCount);
	free(tokenCount);
	str_error(": ");
	str_error(shell_vars->tokens[0]);
	if (err_message)
	{
		str_error(err_message);
	}
	else
		perror("");
}
