#include "main.h"

/**
 * sheller - handles std
 *
 *
 *
 */
void sheller(void)
{
	int cond = 1;
	size_t n = 0;
	char *buf = NULL;

	while (cond)
	{
		write(1, "$ ", 2);
		getline(&buf, &n, stdin);
		write(1, buf, n);
	}
}
