#include "shell.h"

/**
 * INThandler - handles signals and write the prompt
 * @sig: signal to handle
 *
 * Return: void
 */
void INThandler(int sig)
{
	(void)sig;
	write(STDOUT_FILENO, "\n$ ", 3);
}

/**
 * parse_line - Parses the command line looking for commands and argumements.
 * @line: A pointer to a string.
 * @size: A holder for numbers of size_t.
 * @command_counter: A counter keeping track of how many commands have been
 * entered into the shell.
 * @av: Name of the program running the shell
 */

void parse_line(char *line, size_t size, int command_counter, char **av)
{
	int i;
	ssize_t read_len;
	int token_count;
	char **param_array;
	char *dollar = "$ ";
	const char *delim = "\n\t ";

	token_count = 0;
	if (isatty(STDIN_FILENO))
		write(STDOUT_FILENO, dollar, 2);
	/* signal kill for ctrl + c */
	signal(SIGINT, INThandler);
	read_len = getline(&line, &size, stdin);
	if (read_len != -1)
	{
		param_array = token_interface(line, delim, token_count);
		if (param_array[0] == NULL)
		{
			single_free(2, param_array, line);
			return;
		}
		i = built_in(param_array, line);
		if (i == -1)
			create_child(param_array, line, command_counter, av);
		for (i = 0; param_array[i] != NULL; i++)
			free(param_array[i]);
		single_free(2, param_array, line);
	}
	else
		exit_shell(line);
}

/**
 * token_interface - Meant to interact with other token functions.
 * @line: A string containing the raw user input.
 * @delim: A constant string containing the desired delimeter to tokenize line.
 * @token_count: A holder for the amount of tokens in a string.
 *
 * Return: Upon success an array of tokens representing the command. Otherwise
 * returns NULL.
 */
char **token_interface(char *line, const char *delim, int token_count)
{
	char **param_array;

	token_count = count_token(line, delim);
	if (token_count == -1)
	{
		free(line);
		return (NULL);
	}
	param_array = tokenize(token_count, line, delim);
	if (param_array == NULL)
	{
		free(line);
		return (NULL);
	}

	return (param_array);
}

/**
 * tokenize - Separates a string into an array of tokens.
 * @token_count: An integer representing the amount of tokens in the array.
 * @line: String that is separated by an specified delimeter
 * @delim: The desired delimeter to separate tokens.
 *
 * Return: Upon success a NULL terminated array of pointer to strings.
 * Otherwise returns NULL.
 */
char **tokenize(int token_count, char *line, const char *delim)
{
	int i;
	char **buffer;
	char *token;
	char *line_cp;

	line_cp = _strdup(line);
	buffer = malloc(sizeof(char *) * (token_count + 1));
	if (buffer == NULL)
		return (NULL);
	token = strtok(line_cp, delim);
	for (i = 0; token != NULL; i++)
	{
		buffer[i] = _strdup(token);
		token = strtok(NULL, delim);
	}
	buffer[i] = NULL;
	free(line_cp);
	return (buffer);
}

/**
 * count_token - Counts tokens in the passed string.
 * @line: String that is separated by an specified delimeter
 * @delim: The desired delimeter to separate tokens.
 *
 * Return: Upon success the total count of the tokens. Otherwise -1.
 */
int count_token(char *line, const char *delim)
{
	char *str;
	char *token;
	int i;

	str = _strdup(line);
	if (str == NULL)
		return (-1);
	token = strtok(str, delim);
	for (i = 0; token != NULL; i++)
		token = strtok(NULL, delim);
	free(str);
	return (i);
}
