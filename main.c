#include "shell.h"

/**
 * handle_signal - ^C signal
 * @handle_signal: signal variable
 *
 * Return: void
 */
void handle_signal(int handle_signal)
{
	(void) handle_signal;
	str_out("\n$ ");
}

/**
 * main - main function for the shell
 * @argc: number of arguments passed to main
 * @argv: array of arguments passed to main
 * @environment: array of environment variables
 *
 * Return: 0 or exit status, or ?
 */
int main(int argc, char **argv, char **environment)
{
	size_t cmd_mem = 0;
	unsigned int interactive_mode = 0;
	unsigned int i = 0;
	/* initailize shell_vars: tokens , cmd_mem, env_vars, tokenCount, argv, commands, status */
	shell_t shell_vars = {
		NULL, /* tokens */ 
		NULL, /* cmd_mem */
	       	NULL, /* env_vars */
	       	0,    /* tokenCount */
	       	NULL, /* argv */
		NULL, /* commands */
		0};   /* status */

	UNUSED(argc);

	shell_vars.argv = argv;
	/* setting up environment variables */
	shell_vars.env_vars = env_copy(environment);
	signal(SIGINT, handle_signal);

	/* check if the shell is running in interactive mode */
	if (!isatty(STDIN_FILENO))
		interactive_mode = 1;
	/* print "$" if not in interactive mode */
	if (interactive_mode == 0)
		str_out("$ ");

	/* Processing user commands */
	while (getline(&(shell_vars.cmd_mem), &cmd_mem, stdin) != -1)
	{
		shell_vars.tokenCount++;
		/* use ";" as delimiter for tokenization of commands */
		shell_vars.commands = custom_tokenizer(shell_vars.cmd_mem, ";");
		for (; shell_vars.commands && shell_vars.commands[i]; i++)
		{
			/* tokenization of commands using white space */
			shell_vars.tokens = custom_tokenizer(shell_vars.commands[i], "\n \t\r");

			/* check for embedded command and execute in PATH */
			if (shell_vars.tokens && shell_vars.tokens[0])
				if (!(_embedded(&shell_vars)))
					path_check(&shell_vars);
			/* mem free */
			free(shell_vars.tokens);
		}
		/* mem free */
		free(shell_vars.cmd_mem);
		free(shell_vars.commands);

		/* print "$" if not in interactive mode */
		if (interactive_mode == 0)
			str_out("$ ");
		shell_vars.cmd_mem = NULL;
	}

	/* print newline if not in interactive mode */
	if (interactive_mode == 0)
		str_out("\n");

	/* mem free and exit shell*/
	env_free(shell_vars.env_vars);
	free(shell_vars.cmd_mem);
	exit(shell_vars.status);
}
