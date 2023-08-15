#include "main.h"

/**
 * char_check - checks char
 * @str: string
 * @delim: delim
 *
 * Return: int
 */
int char_check(char str[], const char *delim)
{
	unsigned int x, y, z;

	for (x = 0, z = 0; str[x]; x++)
	{
		for (y = 0; delim[y]; y++)
		{
			if (str[x] == delim[y])
			{
				z++;
				break;
			}
		}
	}
	if (x == z)
		return (1);
	return (0);
}

/**
 * _strtok - splits string
 * @str: string
 * @delim: delim
 *
 * Return: token
 */
char *_strtok(char str[], const char *delim)
{
	static char *str_cpy, *str_end;
	char *str_start;
	unsigned int i, found = 0;

	if (str != NULL)
	{
		if (char_check(str, delim))
			return (NULL);
		str_cpy = str;
		i = _strlen(str);
		str_end = &str[i];
	}
	str_start = str_cpy;
	if (str_start == str_end)
		return (NULL);

	for (; *str_cpy; str_cpy++)
	{
		if (str_cpy != str_start)
			if (*str_cpy && *(str_cpy - 1) == '\0')
				break;
		for (i = 0; delim[i]; i++)
		{
			if (*str_cpy == delim[i])
			{
				*str_cpy = '\0';
				if (str_cpy == str_start)
					str_start++;
				break;
			}
		}
		if (found == 0 && *str_cpy)
			found = 1;
	}
	if (found == 0)
		return (NULL);
	return (str_start);
}

/**
 * _strlen - length of str
 * @s: pointer
 * Return: int
 */
int _strlen(const char *s)
{
	int count = 0;

	while (s[count])
		count++;
	return (count);
}

/**
* _strdup - dups a string
*
* @str: str
* Return: *char
*/
char *_strdup(char *str)
{
	char *p;
	unsigned int i;

	if (!str)
	{
		return (NULL);
	}

	for (i = 0; str[i] != '\0'; i++)
	{
	}
	p = (char *) malloc(i + 1);
	if (!p)
		return (NULL);
	for (i = 0; str[i] != '\0'; i++)
	{
		p[i] = str[i];
	}
	p[i] = '\0';
	return (p);

}
