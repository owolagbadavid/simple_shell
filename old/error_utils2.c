#include "main.h"

/**
 * env_err - env error
 * @data: shell data
 * Return: err msg
 */
char *env_err(shell_dt *data)
{
	int len;
	char *error, *count, *msg;

	count = _itoa(data->count);
	msg = ": Unable to add/remove from environment\n";
	len = _strlen(data->av[0]) + _strlen(count);
	len += _strlen(data->args[0]) + _strlen(msg) + 4;
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
	_strcat(error, msg);
	_strcat(error, "\0");
	free(count);

	return (error);
}
/**
 * path_err - path err
 * @data: shell data
 *
 * Return: err msg
 */
char *path_err(shell_dt *data)
{
	int len;
	char *error, *count;

	count = _itoa(data->count);
	len = _strlen(data->av[0]) + _strlen(count);
	len += _strlen(data->args[0]) + 24;
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
	_strcat(error, ": Permission denied\n");
	_strcat(error, "\0");
	free(count);
	return (error);
}
