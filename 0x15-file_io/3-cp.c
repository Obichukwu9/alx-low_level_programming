#include <stdio.h>
#include "main.h"
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>

/**
 * _error - Read file.
 * @e: Error number
 * @filename: File name
 */

void _error(int e, char *filename)
{
	if (e == 98)
	{
		dprintf(STDERR_FILENO, "Error: Can't read from file %s\n", filename);
		exit(98);
	}
	if (e == 99)
	{
		dprintf(STDERR_FILENO, "Error: Can't write to %s\n", filename);
		exit(99);
	}
}

/**
 * cp - Copies the content of a file to another file.
 * @file_from: Name of the source file.
 * @file_to: Name of the destination file.
 * Return: 1 on success, -1 on failure.
 */

void cp(char *file_from, char *file_to)
{
	int f_read, r_read, f_write, r_write;
	char *buf[1024];

	/* READ */
	f_read = open(file_from, O_RDONLY);
	if (f_read < 0)
		_error(98, file_from);
	/* WRITE */
	f_write = open(file_to, O_CREAT | O_WRONLY | O_TRUNC, 0664);
	if (f_write < 0)
	{
		close(f_read);
		_error(99, file_to);
	}
	do {
		/* READ */
		r_read = read(f_read, buf, 1024);
		if (r_read < 0)
			_error(98, file_from);
		/* WRITE */
		r_write = write(f_write, buf, r_read);
		if (r_write < r_read)
			_error(99, file_to);
	}	while (r_write == 1024);
	if (close(f_read) < 0)
	{
		dprintf(STDERR_FILENO, "Error: Can't close fd %d\n", f_read);
		close(f_write);
		exit(100);
	}
	if (close(f_write) < 0)
	{
		dprintf(STDERR_FILENO, "Error: Can't close fd %d\n", f_write);
		exit(100);
	}
}

/**
 * main - Copies the content of a file to another file.
 * @ac: Argument count
 * @av: argument values
 * Return: 0 on succes, -1 on error.
 */

int main(int ac, char *av[])
{
	if (ac != 3)
	{
		dprintf(STDERR_FILENO, "Usage: cp file_from file_to\n");
		exit(97);
	}
	cp(av[1], av[2]);
	return (0);
}
