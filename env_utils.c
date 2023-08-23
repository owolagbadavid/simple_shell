#include "main.h"

/**
 * set_env - sets env
 *
 * @key: key
 * @val: value
 * @data: shell data
 */
void set_env(char *key, char *val, shell_dt *data)
{
	int i;
	char *env_str, *env_toks;

	for (i = 0; data->_env[i]; i++)
	{
		env_str = _strdup(data->_env[i]);
		env_toks = _strtok(env_str, "=");
		if (_strcmp(env_toks, key) == 0)
		{
			free(data->_env[i]);
			data->_env[i] = copy_info(env_toks, val);
			free(env_str);
			return;
		}
		free(env_str);
	}

	data->_env = _realloc2(data->_env, i, sizeof(char *) * (i + 2));
	data->_env[i] = copy_info(key, val);
	data->_env[i + 1] = NULL;
}

/**
 * copy_info - sets value
 * @key: key
 * @val: value
 * Return: str
 */
char *copy_info(char *key, char *val)
{
	char *new;
	int key_len, val_len, len;

	key_len = _strlen(key);
	val_len = _strlen(val);
	len = key_len + val_len + 2;
	new = malloc(sizeof(char) * (len));
	_strcpy(new, key);
	_strcat(new, "=");
	_strcat(new, val);
	_strcat(new, "\0");

	return (new);
}

/**
 * _getenv - gets env by key
 * @key: key
 * @_env: env pointer
 *
 * Return: env
 */
char *_getenv(const char *key, char **_env)
{
	char *ptr_env = NULL;
	int i, match = 0;

	for (i = 0; _env[i]; i++)
	{
		match = cmp_env_key(_env[i], key);
		if (match)
		{
			ptr_env = _env[i];
			break;
		}
	}

	return (ptr_env + match);
}

/**
 * cmp_env_key - cmps
 * @env_key: env key
 * @key: key
 *
 * Return: int
 */
int cmp_env_key(const char *env_key, const char *key)
{
	int i;

	for (i = 0; env_key[i] != '='; i++)
	{
		if (env_key[i] != key[i])
		{
			return (0);
		}
	}

	return (i + 1);
}

/**
 * _env - prints env vars
 *
 * @data: shell data
 * Return: int
 */
int _env(shell_dt *data)
{
	int i, j;

	for (i = 0; data->_env[i]; i++)
	{

		for (j = 0; data->_env[i][j]; j++)
			;

		write(STDOUT_FILENO, data->_env[i], j);
		write(STDOUT_FILENO, "\n", 1);
	}
	data->stat = 0;

	return (1);
}
