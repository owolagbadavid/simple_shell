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
		cond = exec_line(data);
		free(data->args);

		if (cond == 0)
			break;

		next_node(&sep_head, &line_temp, data);

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
