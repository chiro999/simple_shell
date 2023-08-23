#include "shell.h"

/**
 * _execute - executes a command in the path
 * @command: full path to the command
 * @inputs: pointer to struct of variables
 *
 * Return: 0 on succcess, 1 on failure
 */
int _execute(char *command, input_t *inputs)
{
	pid_t child;

	if (access(command, X_OK) == 0)
	{
		child = fork();
		if (child == -1)
			_error(inputs, NULL);
		if (child == 0)
		{
			if (execve(command, inputs->tokens, inputs->env) == -1)
				_error(inputs, NULL);
		}
		else
		{
			wait(&inputs->status);
			if (WIFEXITED(inputs->status))
				inputs->status = WEXITSTATUS(inputs->status);
			else if (WIFSIGNALED(inputs->status) && WTERMSIG(inputs->status) == SIGINT)
				inputs->status = 130;
			return (0);
		}
		inputs->status = 127;
		return (1);
	}
	else
	{
		_error(inputs, ": Permission denied\n");
		inputs->status = 126;
	}
	return (0);
}

/**
 * find_path - finds the PATH variable
 * @env: array of environment variables
 *
 * Return: pointer to the node that contains the PATH, or NULL on failure
 */
char *find_path(char **env)
{
	char *path = "PATH=";
	unsigned int i, j;

	for (i = 0; env[i] != NULL; i++)
	{
		for (j = 0; j < 5; j++)
			if (path[j] != env[i][j])
				break;
		if (j == 5)
			break;
	}
	return (env[i]);

}

/**
 * check_path - checks if the command is in the PATH
 * @inputs: variables
 *
 * Return: void
 */
void check_path(input_t *inputs)
{
	char *path, *dup = NULL, *check = NULL;
	unsigned int i = 0, r = 0;
	char **path_tokens;

	if (check_dir(inputs->tokens[0]))
		r = exec_cwd(inputs);
	else
	{
		path = find_path(inputs->env);
		if (path != NULL)
		{
			dup = _strdup(path + 5);
			path_tokens = tokenize(dup, ":");
			for (i = 0; path_tokens && path_tokens[i]; i++, free(check))
			{
				check = _strcat(path_tokens[i], inputs->tokens[0]);
				if (access(check, F_OK) == 0)
				{
					r = _execute(check, inputs);
					free(check);
					break;
				}
			}
			free(dup);
			if (path_tokens == NULL)
			{
				inputs->status = 127;
				_exit_(inputs);
			}
		}
		if (path == NULL || path_tokens[i] == NULL)
		{
			_error(inputs, ": not found\n");
			inputs->status = 127;
		}
		free(path_tokens);
	}
	if (r == 1)
		_exit_(inputs);
}

/**
 * exec_cwd - executes the command in the current working directory
 * @inputs: pointer to struct of variables
 *
 * Return: 0 on success, 1 on failure
 */
int exec_cwd(input_t *inputs)
{
	pid_t child;

	if (access(inputs->tokens[0], F_OK) == 0)
	{
		if (access(inputs->tokens[0], X_OK) == 0)
		{
			child = fork();
			if (child == -1)
				_error(inputs, NULL);
			if (child == 0)
			{
				if (execve(inputs->tokens[0], inputs->tokens, inputs->env) == -1)
					_error(inputs, NULL);
			}
			else
			{
				wait(&inputs->status);
				if (WIFEXITED(inputs->status))
					inputs->status = WEXITSTATUS(inputs->status);
				else if (WIFSIGNALED(inputs->status) && WTERMSIG(inputs->status) == SIGINT)
					inputs->status = 130;
				return (0);
			}
			inputs->status = 127;
			return (1);
		}
		else
		{
			_error(inputs, ": Permission denied\n");
			inputs->status = 126;
		}
		return (0);
	}
	_error(inputs, ": not found\n");
	inputs->status = 127;
	return (0);
}

/**
 * check_dir - checks if the command is a part of a path
 * @str: command
 *
 * Return: 1 on success, 0 on failure
 */
int check_dir(char *str)
{
	unsigned int i;

	for (i = 0; str[i]; i++)
	{
		if (str[i] == '/')
			return (1);
	}
	return (0);
}
