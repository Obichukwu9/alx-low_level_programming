#include <stdio.h>
#include "main.h"
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>

/**
 * read_textfile -use to  Read a text file and prints it to the POSIX
 * standard output.
 * @filename: file.
 * @letters: Number of letters it should read and print.
 * Return: Actual number of letters it could read and print.
 */

ssize_t read_textfile(const char *filename, size_t letters)
{
	int md, res_read, res_write;
	char *buf;

	if (filename == NULL)
		return (0);
	md = open(filename, O_RDONLY);
	if (md == -1)
		return (0);
	buf = malloc(sizeof(char) * letters);
	if (buf == NULL)
		return (0);
	res_read = read(md, buf, letters);
	if (res_read == -1)
	{
		free(buf);
		return (0);
	}
	res_write = write(STDOUT_FILENO, buf, res_read);
	if (res_write == -1 || res_read != res_write)
	{
		free(buf);
		return (0);
	}
	free(buf);
	close(md);
	return (res_write);
}
