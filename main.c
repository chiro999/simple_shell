#include "shell.h"

/**
 * handle_signal - handles ^C signal interupt
 * @sig_handler: signal handler variable
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
	unsigned int interactive = 0, i;
	shell_t shell_vars = {NULL, NULL, NULL, 0, NULL, NULL, 0};

	UNUSED(argc);

	shell_vars.argv = argv;
	shell_vars.env_vars = env_copy(environment);
	signal(SIGINT, handle_signal);
	if (!isatty(STDIN_FILENO))
		interactive = 1;
	if (interactive == 0)
		str_out("$ ");

	while (getline(&(shell_vars.cmd_mem), &cmd_mem, stdin) != -1)
	{
		shell_vars.tokenCount++;
		shell_vars.commands = custom_tokenizer(shell_vars.cmd_mem, ";");
		for (i = 0; shell_vars.commands && shell_vars.commands[i] != NULL; i++)
		{
			shell_vars.tokens = custom_tokenizer(shell_vars.commands[i], "\n \t\r");
			if (shell_vars.tokens && shell_vars.tokens[0])
				if (_embedded(&shell_vars) == NULL)
					path_check(&shell_vars);
			free(shell_vars.tokens);
		}
		free(shell_vars.cmd_mem);
		free(shell_vars.commands);
		if (interactive == 0)
			str_out("$ ");
		shell_vars.cmd_mem = NULL;
	}
	if (interactive == 0)
		str_out("\n");
	env_free(shell_vars.env_vars);
	free(shell_vars.cmd_mem);
	exit(shell_vars.status);
}
