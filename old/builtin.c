#include "main.h"

/**
 * _cd - change dir
 *
 * @data: shell data
 * Return: int
 */
int _cd(shell_dt *data)
{
	char *dir;
	int ishome, ishome2, isddash;

	dir = data->args[1];

	if (dir != NULL)
	{
		ishome = _strcmp("$HOME", dir);
		ishome2 = _strcmp("~", dir);
		isddash = _strcmp("--", dir);
	}

	if (dir == NULL || !ishome || !ishome2 || !isddash)
	{
		cd_home(data);
		return (1);
	}

	if (_strcmp("-", dir) == 0)
	{
		cd_prev(data);
		return (1);
	}

	if (_strcmp(".", dir) == 0 || _strcmp("..", dir) == 0)
	{
		cd_rel(data);
		return (1);
	}

	cd_to(data);

	return (1);
}


/**
 * _exit_s - exit shell
 *
 * @data: shell data
 * Return: int
 */
int _exit_s(shell_dt *data)
{
	unsigned int status;
	int is_int, str_len, big_number;

	if (data->args[1] != NULL)
	{
		status = _atoi(data->args[1]);
		is_int = _isint(data->args[1]);
		str_len = _strlen(data->args[1]);
		big_number = status > (unsigned int)INT_MAX;
		if (!is_int || str_len > 10 || big_number)
		{
			print_error2(data, 2);
			data->stat = 2;
			return (1);
		}
		data->stat = (status % 256);
	}
	return (0);
}

/**
 * _setenv - set envs
 * @data: shell data
 *
 * Return: int
 */
int _setenv(shell_dt *data)
{

	if (data->args[1] == NULL || data->args[2] == NULL)
	{
		print_error2(data, -1);
		return (1);
	}

	set_env(data->args[1], data->args[2], data);

	return (1);
}

/**
 * _unsetenv - dels env
 *
 * @data: shell data
 * Return: int
 */
int _unsetenv(shell_dt *data)
{
	char **realloc_env;
	char *env_str, *env_toks;
	int i, j, k = -1;

	if (data->args[1] == NULL)
	{
		print_error2(data, k);
		return (1);
	}
	for (i = 0; data->_env[i]; i++)
	{
		env_str = _strdup(data->_env[i]);
		env_toks = _strtok(env_toks, "=");
		if (_strcmp(env_toks, data->args[1]) == 0)
		{
			k = i;
		}
		free(env_str);
	}
	if (k == -1)
	{
		print_error2(data, k);
		return (1);
	}
	realloc_env = malloc(sizeof(char *) * (i));
	for (i = j = 0; data->_env[i]; i++)
	{
		if (i != k)
		{
			realloc_env[j] = data->_env[i];
			j++;
		}
	}
	realloc_env[j] = NULL;
	free(data->_env[k]);
	free(data->_env);
	data->_env = realloc_env;
	return (1);
}

/**
 * _help - help book
 * @data: shell data
 * Return: int
*/
int _help(shell_dt *data)
{

	if (data->args[1] == 0)
		_help_gen();
	else if (_strcmp(data->args[1], "setenv") == 0)
		_help_setenv();
	else if (_strcmp(data->args[1], "env") == 0)
		_help_env();
	else if (_strcmp(data->args[1], "unsetenv") == 0)
		_help_unsetenv();
	else if (_strcmp(data->args[1], "help") == 0)
		_help_help();
	else if (_strcmp(data->args[1], "exit") == 0)
		_help_exit();
	else if (_strcmp(data->args[1], "cd") == 0)
		_help_cd();
	else if (_strcmp(data->args[1], "alias") == 0)
		_help_alias();
	else
		write(STDERR_FILENO, data->args[0],
		      _strlen(data->args[0]));

	data->stat = 0;
	return (1);
}
