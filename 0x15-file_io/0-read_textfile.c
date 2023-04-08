#include <stdio.h>
#include <stdlib.h>
#include "main.h"

/**
 * read_textfile -  reads text file and prints
 * @filename:  pointer variables
 * @letters: size letters
 * Description: Write a function that reads a text file and prints it
 * to the POSIX standard output.
 * Return: the actual number of letters it could read and print, 0 otherwise
 */

ssize_t read_textfile(const char *filename, size_t letters)
{
	char *key; /* pointer to key to read data */
	ssize_t net, door, cut;

	key = malloc(sizeof(char) * letters);
	if (key == NULL)
		return (0);

	if (filename == NULL)
		return (0);

	net = open(filename, O_RDONLY);

	if (net == -1)
	{
		free(key);
		return (0);
	}

	door = read(net, key, letters);

	cut = write(STDOUT_FILENO, key, door);

	close(net);

	return (cut);
}
