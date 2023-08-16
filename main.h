#ifndef __MAIN_H__
#define __MAIN_H__
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <errno.h>
#include <fcntl.h>
#include <signal.h>
#include <limits.h>
#include <stdio.h>
extern char **environ;
void handle_sig(int sig);
int char_check(char str[], const char *delim);
char *_strtok(char str[], const char *delim);
int _strlen(const char *);

/**
 * struct shell_d - shell data
 * @av: argv
 * @input: user input
 * @args: tokens
 * @count: lines
 * @_env: env var
 * @pid: pid of shell
 * @stat: shell status
 */
typedef struct shell_d
{
	char **av;
	char *input;
	char **args;
	int count;
	char **_env;
	char *pid;
	int stat;
} shell_dt;
void sheller(shell_dt *);
void data_init(shell_dt *, char **);
void data_deinit(shell_dt *);
char *_strdup(char *);
char *_itoa(int);
int count_digits(int);
char *remove_comments(char *);
void *_realloc(void *ptr, unsigned int old_size, unsigned int new_size);
char *std_in(int *);
/**
 * struct var_list - linked list for vars
 * @val: value
 * @var_len: var length
 * @val_len: val length
 * @next: next
 */
typedef struct var_list
{
	char *val;
	int var_len;
	int val_len;
	struct var_list *next;
} var_listt;
int vars_check(var_listt **head, char *input, char *status, shell_dt *data);
char *vars_sub(char *input, shell_dt *data);
void check_env(var_listt **head, char *input, shell_dt *data);
char *var_val_sub(var_listt **head, char *input, char *replc_str, int new_len);
var_listt *add_var_list_node(var_listt **head, int var_len, char *val, int val_len);
void free_var_list(var_listt **head);
int find_char_recur(char *input, int i);
int check_syntax(shell_dt *data, char *input);
int check_first_char(char *input, int *index);
void print_error(shell_dt *data, char *input, int i, int is_before);
char *_strcat(char *dest, char *src);
char *_strcpy(char *dest, char *src);
int find_err(char *input, int i, char prev);
#endif
