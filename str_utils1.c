#include "main.h"

/**
* *_strcpy - stuff
*
* @src: pointer
* @dest: pointer
* Return: int
*/
char *_strcpy(char *dest, char *src)
{


	int counter = 0, length = 0;

	while (src[length] != '\0')
	{
		length++;
	}

	while (counter <= length)
	{
		dest[counter] = src[counter];
		counter++;
	}
	return (dest);
}

/**
* *_strcmp - stuff
*
* @s1: pointer
* @s2: pointer
* Return: int
*/
int _strcmp(char *s1, char *s2)
{
	while (*s1 != '\0' && *s2 != '\0' && *s1 == *s2)
	{
		s1++;
		s2++;
	}

	return (*s1 - *s2);
}

/**
* rev_string - stuff
*
* @s: pointer
* Return: void
*/
void rev_string(char *s)
{
	int i;
	char temp;
	int len = _strlen(s);

	for (i = 0; i < len / 2; i++)
	{
		temp = s[i];
		s[i] = s[len - i - 1];
		s[len - i - 1] = temp;
	}


}

/**
 * _atoi - converts string to int
 *
 *
 * @s: string
 *
 * Return: int
 */

int _atoi(char *s)
{
	int sign = 1, i = 0;
	unsigned int num = 0;

	while (!(s[i] <= '9' && s[i] >= '0') && s[i] != '\0')
	{
		if (s[i] == '-')
			sign *= -1;
		i++;
	}
	while (s[i] <= '9' && (s[i] >= '0' && s[i] != '\0'))
	{
		num = (num * 10) + (s[i] - '0');
		i++;
	}
	num *= sign;
	return (num);
}

/**
* _isint - checks if s is digit
*
* @s: The str to check
*
* Return: 1 if true
*/
int _isint(const char *s)
{
	unsigned int i;

	for (i = 0; s[i]; i++)
	{
		if (s[i] < 48 || s[i] > 57)
			return (0);
	}
	return (1);
}
