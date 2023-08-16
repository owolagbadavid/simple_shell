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
