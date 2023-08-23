#include "main.h"

/**
 * _itoa - int to str
 * @n: int
 * Return: str
 */
char *_itoa(int n)
{
	size_t m;
	int len = count_digits(n);
	char *buf;

	buf = malloc(sizeof(char) * (len + 1));
	if (!buf)
		return (NULL);

	*(buf + len) = '\0';

	if (n < 0)
	{
		m = n * -1;
		buf[0] = '-';
	}
	else
		m = n;

	len--;
	do {
		*(buf + len) = (m % 10) + '0';
		m = m / 10;
		len--;
	} while (m > 0);

	return (buf);
}

/**
 * count_digits - int length
 * @n: int
 * Return: len
 */
int count_digits(int n)
{
	size_t m;
	int count = 1;

	if (n < 0)
	{
		count++;
		m = n * -1;
	}
	else
		m = n;
	while (m > 9)
	{
		count++;
		m = m / 10;
	}

	return (count);
}
