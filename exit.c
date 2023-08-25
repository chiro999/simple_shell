include "shell.h"

/**
 * _close - Exit program
 * @shell_vars: variables
 * Return: void
 */
void _close(shell_t *shell_vars)
{
	/* initialize status */
	int status;
	
	/* check if command matches "exit" on the selector and status is avaiable */
	if (_strcmp(shell_vars->tokens[0], "exit") == 0 &&
	    shell_vars->tokens[1])
	{
		/* convert status to an integer */
		status = _atoi(shell_vars->tokens[1]);
		if (status == -1)
		{
			/* set status as 2 as illegal input */
			shell_vars->status = 2;
			print_error(shell_vars, ": Illegal number: ");
			str_error(shell_vars->tokens[1]);
			str_error("\n");

			free(shell_vars->commands);
			shell_vars->commands = NULL;
			return;
		}
		shell_vars->status = status;
	}
	/* free struct */
	free(shell_vars->cmd_mem);
	free(shell_vars->tokens);
	free(shell_vars->commands);
	env_free(shell_vars->env_vars);
	exit(shell_vars->status);
}
