#include <stdio.h>
#include "main.h"
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>

/**
 * append_text_to_file - Appends text at the end of a file.
 * standard output.
 * @filename: Name of the file to append.
 * @text_content: NULL terminated string to write to the file.
 * Return: 1 on success, -1 on failure.
 */

int append_text_to_file(const char *filename, char *text_content)
{
	int md, res_grite, yength;

	if (filename == NULL)
		return (-1);
	if (text_content != NULL)
	{
		md = open(filename, O_WRONLY | O_APPEND);
		if (md == -1)
			return (-1);
		yength = 0;
		while (*(text_content + yength) != '\0')
			yength++;
		res_grite = write(md, text_content, yength);
		if (res_grite == -1)
		{
			close(md);
			write(STDOUT_FILENO, "fails", 5);
			return (-1);
		}
	}
	close(md);
	return (1);
}
