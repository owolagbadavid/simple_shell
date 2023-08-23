#include "main.h"

/**
 * sheller - handles std
 * @data: shell data
 */
void sheller(shell_dt *data)
{
	int result, cond = 1;
	char *input = NULL;

	while (cond)
	{
		if (isatty(STDIN_FILENO))
			write(1, "$ ", 2);
		input = std_in(&result);
		if (result != -1)
		{
			if (is_empty(input))
			{
				write(1, "\n", 1);
				free(input);
				continue;
			}
			input = remove_comments(input);
			if (input == NULL)
				continue;

			if (check_syntax(data, input) == 1)
			{
				data->stat = 2;
				free(input);
				continue;
			}
			input = vars_sub(input, data);
			cond = run_cmds(data, input);
			data->count += 1;
			free(input);
		}
		else
		{
			cond = 0;
			free(input);
		}
	}
}

/**
 * std_in - reads stdin
 *
 * @result: result of getline
 * Return: input
 */
char *std_in(int *result)
{
	char *input = NULL;
	size_t size = 0;

	*result = getline(&input, &size, stdin);
	return (input);
}

/**
 * remove_comments - removes comments
 *
 * @input: str
 * Return: str
 */
char *remove_comments(char *input)
{
	int i, count = 0;

	for (i = 0; input[i]; i++)
	{
		if (input[i] == '#')
		{
			if (i == 0)
			{
				free(input);
				return (NULL);
			}

			if (input[i - 1] == ' ' || input[i - 1] == ';' || input[i - 1] == '\t')
				count = i;
		}
	}

	if (count != 0)
	{
		input = _realloc(input, i, count + 1);
		input[count] = '\0';
	}

	return (input);
}

int is_empty(char *str)
{
	while (*str != '\0')
	{
		if (*str != ' ')
			return (0);
		str++;
	}
	return (1);
}

