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
	(void)av;
	signal(SIGINT, handle_sig);
	sheller();
	return (0);
}
