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
