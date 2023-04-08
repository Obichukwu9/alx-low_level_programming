#include "main.h"

/**
 * append_text_to_file - Appends text .
 * @filename: A pointer to the name of the file.
 * @text_content: The string to add to the end.
 *
 * Return: If the function fails or filename is NULL - -1.
 *         If the file does not exist the user lacks write permissions - -1.
 *         Otherwise - 1.
 */
int append_text_to_file(const char *filename, char *text_content)
{
	int bf = 0, yt, wwrite;

	if (filename == NULL)
		return (-1);

	if (text_content != NULL)
	{
		for (bf = 0; text_content[bf];)
			bf++;
	}

	yt = open(filename, O_WRONLY | O_APPEND);
	wwrite = write(yt, text_content, bf);

	if (yt == -1 || wwrite == -1)
		return (-1);

	close(yt);

	return (1);
}
