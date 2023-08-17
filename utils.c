#include "main.h"

/**
* handle_sig - handle signal int
* @sig: signal
*/
void handle_sig(int __attribute__((__unused__)) sig)
{
	write(1, "\n$ ", 3);
}

/**
 * _realloc - function
 * @ptr: pointer
 * @old_size: int
 * @new_size: int
 *
 * Return: pointer
 */
void *_realloc(void *ptr, unsigned int old_size, unsigned int new_size)
{
	char *np;
	unsigned int i;

	if (new_size == old_size)
		return (ptr);
	if (ptr == NULL)
	{
		np = malloc(new_size);
		if (np == NULL)
		{
			free(np);
			return (NULL);
		}
		return (np);
	}
	if (new_size == 0 && ptr != NULL)
	{
		free(ptr);
		return (NULL);
	}

	np = malloc(new_size);
	if (np == NULL)
	{
		free(np);
		return (NULL);
	}

	for (i = 0; i < old_size; i++)
		np[i] = *((char *)ptr + i);

	free((void *) ptr);
	return (np);
}

/**
 * swap_chars - swaps
 *
 * @input: input
 * @type: type
 * Return: string
 */
char *swap_chars(char *input, int type)
{
	int i;

	if (type == 0)
	{
		for (i = 0; input[i]; i++)
		{
			if (input[i] == '|')
			{
				if (input[i + 1] != '|')
					input[i] = 16;
				else
					i++;
			}

			if (input[i] == '&')
			{
				if (input[i + 1] != '&')
					input[i] = 12;
				else
					i++;
			}
		}
	}
	else
	{
		for (i = 0; input[i]; i++)
		{
			input[i] = (input[i] == 16 ? '|' : input[i]);
			input[i] = (input[i] == 12 ? '&' : input[i]);
		}
	}
	return (input);
}

/**
 * _realloc2 - realloc double p
 * @ptr: double pointer
 * @old_size: size
 * @new_size: new size
 * Return: double pointer
 */
char **_realloc2(char **ptr, unsigned int old_size, unsigned int new_size)
{
	char **newptr;
	unsigned int i;

	if (ptr == NULL)
		return (malloc(sizeof(char *) * new_size));

	if (new_size == old_size)
		return (ptr);

	newptr = malloc(sizeof(char *) * new_size);
	if (newptr == NULL)
		return (NULL);

	for (i = 0; i < old_size; i++)
		newptr[i] = ptr[i];

	free(ptr);

	return (newptr);
}
