#include "main.h"

/**
 * print_error2 - prints error
 * @data: shell data
 * @e_val: err val
 * Return: err val
 */
int print_error2(shell_dt *data, int e_val)
{
	char *error;

	switch (e_val)
	{
	case -1:
		error = env_err(data);
		break;
	case 126:
		error = path_err(data);
		break;
	case 127:
		error = not_found_err(data);
		break;
	case 2:
		if (_strcmp("exit", data->args[0]) == 0)
			error = exit_shell_err(data);
		else if (_strcmp("cd", data->args[0]) == 0)
			error = _cd_err(data);
		break;
	}

	if (error)
	{
		write(2, error, _strlen(error));
		free(error);
	}

	data->stat = e_val;
	return (e_val);
}

/**
 * _cd_err - cd error
 * @data: shell data
 * Return: err msg
 */
char *_cd_err(shell_dt *data)
{
	int len, len2;
	char *error, *count, *msg;

	count = _itoa(data->count);
	if (data->args[1][0] == '-')
	{
		msg = ": Illegal option ";
		len2 = 2;
	}
	else
	{
		msg = ": can't cd to ";
		len2 = _strlen(data->args[1]);
	}

	len = _strlen(data->av[0]) + _strlen(data->args[0]);
	len += _strlen(count) + _strlen(msg) + len2 + 5;
	error = malloc(sizeof(char) * (len + 1));

	if (error == 0)
	{
		free(count);
		return (NULL);
	}

	error = strcat_err_cd(data, msg, error, count);

	free(count);

	return (error);
}

/**
 * strcat_err_cd - concat err smg
 *
 * @data: shell data
 * @msg: msg
 * @error: msg
 * @count: count
 * Return: err msg
 */
char *strcat_err_cd(shell_dt *data, char *msg, char *error, char *count)
{
	char *err_p;

	_strcpy(error, data->av[0]);
	_strcat(error, ": ");
	_strcat(error, count);
	_strcat(error, ": ");
	_strcat(error, data->args[0]);
	_strcat(error, msg);
	if (data->args[1][0] == '-')
	{
		err_p = malloc(3);
		err_p[0] = '-';
		err_p[1] = data->args[1][1];
		err_p[2] = '\0';
		_strcat(error, err_p);
		free(err_p);
	}
	else
	{
		_strcat(error, data->args[1]);
	}

	_strcat(error, "\n");
	_strcat(error, "\0");
	return (error);
}

/**
 * not_found_err - cmd not found
 * @data: shell data
 * Return: err msg
 */
char *not_found_err(shell_dt *data)
{
	int len;
	char *error, *count;

	count = _itoa(data->count);
	len = _strlen(data->av[0]) + _strlen(count);
	len += _strlen(data->args[0]) + 16;
	error = malloc(sizeof(char) * (len + 1));
	if (error == 0)
	{
		free(error);
		free(count);
		return (NULL);
	}
	_strcpy(error, data->av[0]);
	_strcat(error, ": ");
	_strcat(error, count);
	_strcat(error, ": ");
	_strcat(error, data->args[0]);
	_strcat(error, ": not found\n");
	_strcat(error, "\0");
	free(count);
	return (error);
}

/**
 * exit_shell_err - exit shell error
 * @data: shell data
 *
 * Return: err msg
 */
char *exit_shell_err(shell_dt *data)
{
	int len;
	char *error, *count;

	count = _itoa(data->count);
	len = _strlen(data->av[0]) + _strlen(count);
	len += _strlen(data->args[0]) + _strlen(data->args[1]) + 23;
	error = malloc(sizeof(char) * (len + 1));
	if (error == 0)
	{
		free(count);
		return (NULL);
	}
	_strcpy(error, data->av[0]);
	_strcat(error, ": ");
	_strcat(error, count);
	_strcat(error, ": ");
	_strcat(error, data->args[0]);
	_strcat(error, ": Illegal number: ");
	_strcat(error, data->args[1]);
	_strcat(error, "\n\0");
	free(count);

	return (error);
}
