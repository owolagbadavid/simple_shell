#include "main.h"

/**
 * run_cmds - runs commans
 * @data: shell data
 * @input: input
 * Return: int 1 success
 */
int run_cmds(shell_dt *data, char *input)
{

	sep_listt *sep_head, *sep_temp;
	cline_listt *line_head, *line_temp;
	int cond;

	sep_head = NULL;
	line_head = NULL;

	add_nodes(&sep_head, &line_head, input);

	sep_temp = sep_head;
	line_temp = line_head;

	while (line_temp != NULL)
	{
		data->input = line_temp->line;
		data->args = split_cmd(data->input);
		cond = exec_cmd(data);
		free(data->args);

		if (cond == 0)
			break;

		next_node(&sep_temp, &line_temp, data);

		if (line_temp != NULL)
			line_temp = line_temp->next;
	}

	free_sep_list(&sep_head);
	free_line_list(&line_head);

	if (cond == 0)
		return (cond);
	return (1);
}

/**
 * split_cmd - splits commands
 *
 * @input: input
 * Return: str
 */
char **split_cmd(char *input)
{
	size_t bsize = TOKEN_BUF, i;
	char *token, **tokens;

	tokens = malloc(sizeof(char *) * (bsize));
	if (tokens == NULL)
	{
		write(2, ": allocation error\n", 18);
		exit(EXIT_FAILURE);
	}

	token = _strtok(input, TOKEN_DELIM);
	tokens[0] = token;

	for (i = 1; token != NULL; i++)
	{
		if (i == bsize)
		{
			bsize += TOKEN_BUF;
			tokens = _realloc2(tokens, i, sizeof(char *) * bsize);
			if (tokens == NULL)
			{
				write(2, ": allocation error\n", 18);
				exit(EXIT_FAILURE);
			}
		}
		token = _strtok(NULL, TOKEN_DELIM);
		tokens[i] = token;
	}

	return (tokens);
}

/**
 * exec_cmd - handles execute
 *
 * @data: shell data
 * Return: int
 */
int exec_cmd(shell_dt *data)
{
	int (*builtin)(shell_dt *data);

	if (data->args[0] == NULL)
		return (1);

	builtin = get_builtin(data->args[0]);

	if (builtin != NULL)
		return (builtin(data));

	return (exec_ext(data));
}

/**
 * get_builtin - builtin func
 * @cmd: command
 * Return: func
 */
int (*get_builtin(char *cmd))(shell_dt *)
{
	builtin_ct builtin[] = {
		{ "cd", _cd },
		{ "exit", _exit_s},
		{ "env", _env },
		{ "setenv", _setenv },
		{ "unsetenv", _unsetenv },
		{ "help", _help },
		{ NULL, NULL }
	};
	int i;

	for (i = 0; builtin[i].name; i++)
	{
		if (_strcmp(builtin[i].name, cmd) == 0)
			break;
	}

	return (builtin[i].func);
}

/**
 * exec_ext - execute cmd
 *
 * @data: shell data
 * Return: int
 */
int exec_ext(shell_dt *data)
{
	pid_t pd;
	pid_t wpd;
	int state;
	int exec;
	char *dir;
	(void) wpd;

	exec = is_executable(data);
	if (exec == -1)
		return (1);
	if (exec == 0)
	{
		dir = _which(data->args[0], data->_env);
		if (check_error_cmd(dir, data) == 1)
			return (1);
	}

	pd = fork();
	if (pd == 0)
	{
		if (exec == 0)
			dir = _which(data->args[0], data->_env);
		else
			dir = data->args[0];
		execve(dir + exec, data->args, data->_env);
	}
	else if (pd < 0)
	{
		perror(data->av[0]);
		return (1);
	}
	else
	{
		do {
			wpd = waitpid(pd, &state, WUNTRACED);
		} while (!WIFEXITED(state) && !WIFSIGNALED(state));
	}

	data->stat = state / 256;
	return (1);
}
