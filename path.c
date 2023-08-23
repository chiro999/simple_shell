#include "shell.h"

/**
 * _execute - executes a command in the path
 * @command: full path to the command
 * @shell_vars: pointer to struct of variables
 *
 * Return: 0 on succcess, 1 on failure
 */
int _execute(char *command, shell_t *shell_vars)
{
	pid_t child;

	if (access(command, X_OK) == 0)
	{
		/* create child process using fork */
		child = fork();

		/* if it is negative an error occured */
		if (child == -1)
			print_error(shell_vars, NULL);
		/*if the child process occured 0 */
		if (child == 0)
		{
			if (execve(command, shell_vars->tokens, shell_vars->env_vars) == -1)
				print_error(shell_vars, NULL);
		}
		/* if it is the parent process that is running */
		else
		{
			wait(&shell_vars->status);
			if (WIFEXITED(shell_vars->status))
				shell_vars->status = WEXITSTATUS(shell_vars->status);
			else if (WIFSIGNALED(shell_vars->status) && WTERMSIG(shell_vars->status) == SIGINT)
				shell_vars->status = 130;
			return (0);
		}
		shell_vars->status = 127;
		return (1);
	}
	/* if user lacks permission to execute command */
	else
	{
		print_error(shell_vars, ": Permission denied\n");
		shell_vars->status = 126;
	}
	return (0);
}

/**
 * str_path - find the PATH variable
 * @env_arr:  environment variables
 *
 * Return: the node that contains the PATH, or NULL on failure
 */
char *str_path(char **env_arr)
{
	char *path = "PATH=";
	unsigned int i, j;

	/* for loop to check which env_arr has 5 characters and is equal to 'PATH='*/
	for (i = 0; env_arr[i] != NULL; i++)
	{
		for (j = 0; j < 5; j++)
			if (path[j] != env_arr[i][j])
				break;
		if (j == 5)
			break;
	}
	return (env_arr[i]);

}

/**
 * path_check - check if  the command resides in the PATH
 * @shell_vars: variables
 *
 * Return: void
 */
void path_check(shell_t *shell_vars)
{
	char *path, *dup = NULL, *check = NULL;
	unsigned int i = 0, exec_check = 0;
	char **path_tokens;
	
	/* is command in the current directory */
	if (is_PATH(shell_vars->tokens[0]))
		exec_check = exec_curr_dir(shell_vars);
	else
	{	
		/* find PATH from env variables */
		path = str_path(shell_vars->env_vars);
		if (path != NULL)
		{
			dup = _strdup(path + 5);
			path_tokens = custom_tokenizer(dup, ":");
			for (i = 0; path_tokens && path_tokens[i]; i++, free(check))
			{
				check = _strcat(path_tokens[i], shell_vars->tokens[0]);
				/* does command file exist */
				if (access(check, F_OK) == 0)
				{
					exec_check = _execute(check, shell_vars);
					free(check);
					break;
				}
			}
			/* free memory */
			free(dup);
			/* if no paths */
			if (path_tokens == NULL)
			{
				shell_vars->status = 127;
				_close(shell_vars);
			}
		}
		/* if the command is not in any path- print error message */
		if (path == NULL || path_tokens[i] == NULL)
		{
			print_error(shell_vars, ": not found\n");
			shell_vars->status = 127;
		}
		free(path_tokens);
	}
	/* close if execution is succesful */
	if (exec_check == 1)
		_close(shell_vars);
}

/**
 * exec_curr_dir - executes command in the current  directory
 * @shell_vars: struct of variables
 *
 * Return: 0 on success, 1 on failure
 */
int exec_curr_dir(shell_t *shell_vars)
{
	pid_t child;
	
	/* does command file exist */
	if (access(shell_vars->tokens[0], F_OK) == 0)
	{	
		/* is command file executable */
		if (access(shell_vars->tokens[0], X_OK) == 0)
		{	
			/* create child process using fork */
			child = fork();
			/* failed to create child process */
			if (child == -1)
				print_error(shell_vars, NULL);
			/* child process */
			if (child == 0)
			{	
				/* check for execution failure */
				if (execve(shell_vars->tokens[0], shell_vars->tokens, shell_vars->env_vars) == -1)
					print_error(shell_vars, NULL);
			}
			/* parent process */
			else
			{
				/* wait for the child process to complete and check the exit status of child process */
				wait(&shell_vars->status);
				if (WIFEXITED(shell_vars->status))
					shell_vars->status = WEXITSTATUS(shell_vars->status);
				else if (WIFSIGNALED(shell_vars->status) && WTERMSIG(shell_vars->status) == SIGINT)
					shell_vars->status = 130;
				return (0);
			}
			/* fork failed */
			shell_vars->status = 127;
			return (1);
		}
		else
		{
			print_error(shell_vars, ": Permission denied\n");
			shell_vars->status = 126;
		}
		return (0);
	}
	print_error(shell_vars, ": not found\n");
	shell_vars->status = 127;
	return (0);
}

/**
 * is_PATH - checks if the command is a part of a path
 * @str: command
 *
 * Return: 1 on success, 0 on failure
 */
int is_PATH(char *name)
{
	unsigned int i;
	/* search for path separator '/' */
	for (i = 0; name[i]; i++)
	{
		if (name[i] == '/')
			return (1);
	}
	return (0);
}
