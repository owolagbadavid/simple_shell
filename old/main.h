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
#define BUFSIZE 1024
#define TOKEN_BUF 128
#define TOKEN_DELIM " \n\t\r\a"

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
var_listt *add_var_list_node(var_listt **head, int var_len,
		char *val, int val_len);
void free_var_list(var_listt **head);
int find_char_recur(char *input, int i);
int check_syntax(shell_dt *data, char *input);
int check_first_char(char *input, int *index);
void print_error(shell_dt *data, char *input, int i, int is_before);
char *_strcat(char *dest, char *src);
char *_strcpy(char *dest, char *src);
int find_err(char *input, int i, char prev);
int run_cmds(shell_dt *data, char *input);
/**
 * struct sep_list - linked list
 * @sep: arator
 * @next: next
 */
typedef struct sep_list
{
	char sep;
	struct sep_list *next;
} sep_listt;

/**
 * struct cline_list - linked list
 * @line: cmd line
 * @next: next
 */
typedef struct cline_list
{
	char *line;
	struct cline_list *next;
} cline_listt;
void add_nodes(sep_listt **sep_head, cline_listt **line_head, char *input);
cline_listt *add_line_node(cline_listt **head, char *line);
sep_listt *add_sep_node(sep_listt **head, char sep);
void free_line_list(cline_listt **head);
void free_sep_list(sep_listt **head);
char **_realloc2(char **ptr, unsigned int old_size, unsigned int new_size);
void next_node(sep_listt **sep_l, cline_listt **line_l, shell_dt *data);
char **split_cmd(char *input);
char *swap_chars(char *input, int type);

/**
 * struct builtin_c - builtin command
 * @name: command name
 * @func: command func
 */
typedef struct builtin_c
{
	char *name;
	int (*func)(shell_dt *data);
} builtin_ct;
int exec_cmd(shell_dt *data);
int _strcmp(char *s1, char *s2);
int (*get_builtin(char *cmd))(shell_dt *);
int _cd(shell_dt *data);
void cd_rel(shell_dt *data);
void rev_string(char *s);
void cd_to(shell_dt *data);
void cd_home(shell_dt *data);
void cd_prev(shell_dt *data);
void set_env(char *key, char *val, shell_dt *data);
char *copy_info(char *key, char *val);
char *_getenv(const char *key, char **_env);
int cmp_env_key(const char *env_key, const char *key);
char *_cd_err(shell_dt *data);
char *strcat_err_cd(shell_dt *data, char *msg, char *error, char *count);
char *not_found_err(shell_dt *data);
char *exit_shell_err(shell_dt *data);
int print_error2(shell_dt *data, int e_val);
char *path_err(shell_dt *data);
char *env_err(shell_dt *data);
int check_error_cmd(char *dir, shell_dt *data);
int is_cur_dir(char *path, int *i);
char *_which(char *cmd, char **_env);
int is_executable(shell_dt *data);
int exec_ext(shell_dt *data);
int _exit_s(shell_dt *data);
int _atoi(char *s);
int _isint(const char *s);
int _setenv(shell_dt *data);
int _unsetenv(shell_dt *data);
int _help(shell_dt *data);
void _help_exit(void);
void _help_unsetenv(void);
void _help_env(void);
void _help_setenv(void);
void _help_gen(void);
void _help_alias(void);
void _help_cd(void);
void _help_help(void);
int is_empty(char *str);
int _env(shell_dt *data);
#endif
