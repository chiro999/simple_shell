#include "shell.h"

/**
 * _close - Exit program
 * @shell_vars: variables
 * Return: void
 */
void _close(shell_t *shell_vars)
{
	int status;

	if (_strncmp(shell_vars->tokens[0], "exit") == 0 &&
	    shell_vars->tokens[1] != NULL)
	{
		status = _atoi(shell_vars->tokens[1]);
		if (status == -1)
		{
			shell_vars->status = 2;
			print_error(inputs, ": Illegal number: ");
			str_error(inputs->tokens[1]);
			str_error("\n");
			free(shell-vars->commands);
			shell_vars->commands = NULL;
			return;
		}
		shell_vars->status = status;
	}
	free(shell_vars->cmd_mem);
	free(shell_vars->tokens);
	free(shell_vars->commands);
	env_free(shell_vars->env_vars);
	exit(shell_vars->status);
}
