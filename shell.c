#ifndef _SHELL_H_
#define _SHELL_H_

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <limits.h>
#include <signal.h>


#define UNUSED(x) (void)(x)

/**
 * struct input - variables
 * @tokens: command line arguments
 * @buffer: buffer of command
 * @env: environment variables
 * @count: count of commands entered
 * @argv: arguments at opening of shell
 * @status: exit status
 * @commands: commands to execute
 */
typedef struct input
{
	char **tokens;
	char *buffer;
	char **env;
	size_t count;
	char **argv;
	int status;
	char **commands;
} input_t;

/**
 * struct builtins - struct for the builtin functions
 * @name: name of builtin command
 * @f: function for corresponding builtin
 */
typedef struct builtins
{
	char *name;
	void (*f)(input_t *);
} builtins_t;

void sig_handler(int sig_handler);
char **init_env(char **env);
void free_environ(char **env);

ssize_t _puts(char *s);
char *_strdup(char *duplicate);
char *_strcat(char *dest, char *src);
unsigned int _strlen(char *s);

/* memory management: _realloc.c */
char **_realloc(char **ptr, size_t *size);

void (*_builtins(input_t *inputs))(input_t *inputs);
void _exit_(input_t *inputs);
void _env(input_t *inputs);
void _setenv(input_t *inputs);
void _unsetenv(input_t *inputs);

int _strncmp(char *s1, char *s2);


void add_env(input_t *inputs);
char **find_env(char **env, char *path);
char *add_value(char *path, char *value);
int _atoi(char *s);

void check_path(input_t *inputs);
int _execute(char *command, input_t *inputs);
char *find_path(char **env);
int exec_cwd(input_t *inputs);
int check_dir(char *s);

void _error(input_t *inputs, char *message);
void _printer(char *str);
char *_int_str(unsigned int count);

/* _strtok & tokenize: _strtok.c & tokenizer.c */
unsigned int matching(char c, const char *str);
char *_strtok(char *str, const char *delim);
char **tokenize(char *arguments, char *delimiter);

#endif /* _SHELL_H_ */
