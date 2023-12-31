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
 * struct shell_vars - Variables for the shell
 * @tokens: Command line arguments
 * @cmd_mem: Memory for command
 * @env_vars: Environment variables
 * @tokenCount: Count of tokens
 * @argv: Arguments at opening of shell
 * @close_status: Exit status
 * @commands: Commands to execute
 */
typedef struct shell_vars
{
    char **tokens;
    char *cmd_mem;
    char **env_vars;
    size_t tokenCount;
    char **argv;
    char **commands;
    int status;
} shell_t;

/**
 * struct embedded - Embedded functions struct
 * @name: embedded command
 * @f: embedded function
 */
typedef struct embedded
{
    char *name;
    void (*f)(shell_t *);
} embedded_t;

/* PATH functions */
int _execute(char *command, shell_t *shell_vars);
char *str_path(char **env_arr);
int exec_curr_dir(shell_t *shell_vars);
void path_check(shell_t *shell_vars);
int is_PATH(char *name);

/* close function */
void _close(shell_t *shell_vars);

/* strtok functions */
unsigned int is_a_match(char x, const char *str);
char *custom_strtok(char *str, const char *delim);

/* tokenizer function */
char **custom_tokenizer(char *args, char *delim);

/* embedded functions */
void curr_env(shell_t *shell_vars);
void _setenv(shell_t *shell_vars);
void _unsetenv(shell_t *shell_vars);
void (*_embedded(shell_t *shell_vars))(shell_t *shell_vars);

/* environment functions */
char **find_env(char **env, char *path);
void env_free(char **environ);
char **env_copy(char **environ);
char *new_env(char *key, char *value);
void env_plus(shell_t *shell_vars);

/* stdlib replacements */
char *_strcat(char *dest, char *src);
int _strcmp(char *s1, char *s2);
int _atoi(char *s);

ssize_t str_out(char *string);
unsigned int _strlen(char *s);
void str_error(char *string);

char *_strdup(char *replica);
char *int_to_string(unsigned int count);

/* memory reallocation function */
char **more_mem(char **old_arr, size_t *n);

/* print error function */
void print_error(shell_t *shell_vars, char *err_message);

/* main functions */
void handle_signal(int handle_signal);
int main(int argc, char **argv_arr, char **env_arr);

#endif
