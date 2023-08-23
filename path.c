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
		child = fork();
		if (child == -1)
			print_error(shell_vars, NULL);
		if (child == 0)
		{
			if (execve(command, shell_vars->tokens, shell_vars->env_vars) == -1)
				print_error(shell_vars, NULL);
		}
		else
		{
			wait(&shell_vars->status);
			if (WIFEXITED(shell_vars->status))
				shell_vars->status = WEXITSTATUS(shell_vars->status);
			else if (WIFSIGNALED(shell_vars->status) && WTERMSIG(shell_vars->status) == SIGINT)
				shell_varss->status = 130;
			return (0);
		}
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

/**
 * str_path - finds the PATH variable
 * @env: array of environment variables
 *
 * Return: pointer to the node that contains the PATH, or NULL on failure
 */
char *str_path(char **env_arr)
{
	char *path = "PATH=";
	unsigned int i, j;

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
 * path_check - checks if the command is in the PATH
 * @inputs: variables
 *
 * Return: void
 */
void path_check(input_t *inputs)
{
	char *path, *dup = NULL, *check = NULL;
	unsigned int i = 0, r = 0;
	char **path_tokens;

	if (check_dir(shell_vars->tokens[0]))
		r = exec_cwd(shell_vars);
	else
	{
		path = find_path(shell_vars->env_vars);
		if (path != NULL)
		{
			dup = _strdup(path + 5);
			path_tokens = tokenize(dup, ":");
			for (i = 0; path_tokens && path_tokens[i]; i++, free(check))
			{
				check = _strcat(path_tokens[i], shell_vars->tokens[0]);
				if (access(check, F_OK) == 0)
				{
					r = _execute(check, shell_vars);
					free(check);
					break;
				}
			}
			free(dup);
			if (path_tokens == NULL)
			{
				shell_vars->status = 127;
				_close(shell_vars);
			}
		}
		if (path == NULL || path_tokens[i] == NULL)
		{
			print_error(shell_vars, ": not found\n");
			shell_vars->status = 127;
		}
		free(path_tokens);
	}
	if (r == 1)
		_close(shell_vars);
}

/**
 * exec_curr_dir - executes the command in the current working directory
 * @shell_vars: pointer to struct of variables
 *
 * Return: 0 on success, 1 on failure
 */
int exec_curr_dir(shell_t *shell_vars)
{
	pid_t child;

	if (access(shell_vars->tokens[0], F_OK) == 0)
	{
		if (access(shell_vars->tokens[0], X_OK) == 0)
		{
			child = fork();
			if (child == -1)
				print_error(shell_vars, NULL);
			if (child == 0)
			{
				if (execve(shell_vars->tokens[0], shell_vars->tokens, shell->env_vars) == -1)
					print_error(shell_vars, NULL);
			}
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

	for (i = 0; name[i]; i++)
	{
		if (name[i] == '/')
			return (1);
	}
	return (0);
}
