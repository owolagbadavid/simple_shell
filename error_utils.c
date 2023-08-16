#include "main.h"

/**
 * check_syntax - cheks for syntax err
 *
 * @data: shell data
 * @input: input
 * Return: int
 */
int check_syntax(shell_dt *data, char *input)
{
	int start = 0;
	int is_error = 0;
	int i = 0;

	is_error = check_first_char(input, &start);
	if (is_error)
	{
		print_error(data, input, start, 0);
		return (1);
	}

	i = find_err(input + start, 0, *(input + start));
	if (i != 0)
	{
		print_error(data, input, start + i, 1);
		return (1);
	}

	return (0);
}

/**
 * check_first_char - finds the first character and chek for error
 *
 * @input: input
 * @index: index
 * Return: int
 */
int check_first_char(char *input, int *index)
{

	for (*index = 0; input[*index]; *index += 1)
	{
		if (input[*index] == ' ' || input[*index] == '\t')
			continue;

		if (input[*index] == ';' || input[*index] == '|' || input[*index] == '&')
			return (1);

		break;
	}

	return (0);
}

/**
 * print_error - print eror
 *
 * @data: shell data
 * @input: input
 * @i: error index
 * @is_before: bool
 */
void print_error(shell_dt *data, char *input, int i, int is_before)
{
	char *msg, *msg2 = ": Syntax error: \"", *msg3 = "\" unexpected\n";
	char *error, *count;
	int len;

	if (input[i] == ';')
	{
		if (is_before == 0)
			msg = (input[i + 1] == ';' ? ";;" : ";");
		else
			msg = (input[i - 1] == ';' ? ";;" : ";");
	}

	if (input[i] == '|')
		msg = (input[i + 1] == '|' ? "||" : "|");

	if (input[i] == '&')
		msg = (input[i + 1] == '&' ? "&&" : "&");

	count = _itoa(data->count);
	len = _strlen(data->av[0]) + _strlen(count);
	len += _strlen(msg) + _strlen(msg2) + _strlen(msg3) + 2;

	error = malloc(sizeof(char) * (len + 1));
	if (error == 0)
	{
		free(count);
		return;
	}
	_strcpy(error, data->av[0]);
	_strcat(error, ": ");
	_strcat(error, count);
	_strcat(error, msg2);
	_strcat(error, msg);
	_strcat(error, msg3);
	_strcat(error, "\0");

	write(2, error, len);
	free(error);
	free(count);
}

/**
 * find_err - find syntax err
 *
 * @input: input
 * @i: index
 * @prev: char
 * Return: int
 */
int find_err(char *input, int i, char prev)
{
	int reps = 0;

	if (*input == '\0')
		return (0);

	if (*input == ' ' || *input == '\t')
		return (find_err(input + 1, i + 1, prev));

	if (*input == ';')
		if (prev == '|' || prev == '&' || prev == ';')
			return (i);

	if (*input == '|')
	{
		if (prev == ';' || prev == '&')
			return (i);

		if (prev == '|')
		{
			reps = find_char_recur(input, 0);
			if (reps == 0 || reps > 1)
				return (i);
		}
	}

	if (*input == '&')
	{
		if (prev == ';' || prev == '|')
			return (i);

		if (prev == '&')
		{
			reps = find_char_recur(input, 0);
			if (reps == 0 || reps > 1)
				return (i);
		}
	}

	return (find_err(input + 1, i + 1, *input));
}

/**
 * find_char_recur - find chars
 *
 * @input: input
 * @i: index
 * Return: int
 */
int find_char_recur(char *input, int i)
{
	if (*(input - 1) == *input)
		return (find_char_recur(input - 1, i + 1));

	return (i);
}
