#include "shell.h"

/**
 * main - basic shell recreation
 * @ac: argument count
 * @av: argument vector
 *
 * Return: Always 0
 */

int main(__attribute__((unused))int ac, char **av)
{
	char *line;
	size_t size;
	int command_counter;

	command_counter = 0;
	do {
		command_counter++;
		line = NULL;
		size = 0;
		parse_line(line, size, command_counter, av);

	} while (1);

	return (0);
}

