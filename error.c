#include "shell.h"

/**
 * print_error - record error messages to standard error
 * @shell_vars: pointer to struct of variables
 * @err_message: message to be sent to standard error
 *
 * Return: void
 */
void print_error(shell_t *shell_vars, char *err_message)
{
	char *tokenCount;
	/* print program name */
	str_error(shell_vars->argv[0]);
	/* program name formatting */
	str_error(": ");
	tokenCount = int_to_string(shell_vars->tokenCount);
	str_error(tokenCount);
	free(tokenCount);
	str_error(": ");
	/* print the token causing the error */
	str_error(shell_vars->tokens[0]);
	if (err_message)
	{
		str_error(err_message);
	}
	else
		perror("");
}
