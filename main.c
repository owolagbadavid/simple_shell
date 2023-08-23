#include "main.h"

/**
 * main - Entry point
 *
 * @ac: no of args
 * @av: args
 *
 * Return: int
 */
int main(int __attribute__((__unused__)) ac, char **av)
{
	shell_dt data;

	/*signal(SIGINT, handle_sig);*/
	data_init(&data, av);
	sheller(&data);
	data_deinit(&data);

	if (data.stat < 0)
		return (255);
	return (data.stat);
}

/**
 * data_init - init shell data
 *
 * @data: shell data
 * @av: argv
 */
void data_init(shell_dt *data, char **av)
{
	size_t i = 0;

	data->av = av;
	data->input = NULL;
	data->args = NULL;
	data->stat = 0;
	data->count = 1;

	while (environ[i])
		i++;

	data->_env = malloc(sizeof(char *) * (i + 1));

	for (i = 0; environ[i]; i++)
	{
		data->_env[i] = _strdup(environ[i]);
	}

	data->_env[i] = NULL;
	data->pid = _itoa(getpid());
}

/**
 * data_deinit - deinit data
 *
 * @data: shell data
 */
void data_deinit(shell_dt *data)
{
	size_t i;

	for (i = 0; data->_env[i]; i++)
	{
		free(data->_env[i]);
	}

	free(data->_env);
	free(data->pid);
}
