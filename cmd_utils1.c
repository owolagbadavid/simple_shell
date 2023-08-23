#include "main.h"

/**
 * _which - locates command
 *
 * @cmd: command name
 * @_env: env
 * Return: cmd location
 */
char *_which(char *cmd, char **_env)
{
	char *path, *ptr_path, *token_path, *dir;
	int len_dir, len_cmd, i;
	struct stat st;

	path = _getenv("PATH", _env);
	if (path)
	{
		ptr_path = _strdup(path);
		len_cmd = _strlen(cmd);
		token_path = _strtok(ptr_path, ":");
		i = 0;
		while (token_path != NULL)
		{
			if (is_cur_dir(path, &i))
				if (stat(cmd, &st) == 0)
					return (cmd);
			len_dir = _strlen(token_path);
			dir = malloc(len_dir + len_cmd + 2);
			_strcpy(dir, token_path);
			_strcat(dir, "/");
			_strcat(dir, cmd);
			_strcat(dir, "\0");
			if (stat(dir, &st) == 0)
			{
				free(ptr_path);
				return (dir);
			}
			free(dir);
			token_path = _strtok(NULL, ":");
		}
		free(ptr_path);
		if (stat(cmd, &st) == 0)
			return (cmd);
		return (NULL);
	}
	if (cmd[0] == '/')
		if (stat(cmd, &st) == 0)
			return (cmd);
	return (NULL);
}

/**
 * is_cur_dir - if cmd is in cwd
 * @path: str
 * @i: int pointer
 * Return: int
 */
int is_cur_dir(char *path, int *i)
{
	if (path[*i] == ':')
		return (1);

	while (path[*i] != ':' && path[*i])
	{
		*i += 1;
	}

	if (path[*i])
		*i += 1;

	return (0);
}

/**
 * is_executable - check if executable
 *
 * @data: shell data
 * Return: bool
 */
int is_executable(shell_dt *data)
{
	struct stat st;
	int i;
	char *input;

	input = data->args[0];
	for (i = 0; input[i]; i++)
	{
		if (input[i] == '.')
		{
			if (input[i + 1] == '.')
				return (0);
			if (input[i + 1] == '/')
				continue;
			else
				break;
		}
		else if (input[i] == '/' && i != 0)
		{
			if (input[i + 1] == '.')
				continue;
			i++;
			break;
		}
		else
			break;
	}
	if (i == 0)
		return (0);

	if (stat(input + i, &st) == 0)
	{
		return (i);
	}
	print_error2(data, 127);
	return (-1);
}

/**
 * check_error_cmd - user can?
 *
 * @dir: dir
 * @data: shell data
 * Return: int
 */
int check_error_cmd(char *dir, shell_dt *data)
{
	if (dir == NULL)
	{
		print_error2(data, 127);
		return (1);
	}

	if (_strcmp(data->args[0], dir) != 0)
	{
		if (access(dir, X_OK) == -1)
		{
			print_error2(data, 126);
			free(dir);
			return (1);
		}
		free(dir);
	}
	else
	{
		if (access(data->args[0], X_OK) == -1)
		{
			print_error2(data, 126);
			return (1);
		}
	}

	return (0);
}


