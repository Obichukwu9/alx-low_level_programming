#include "main.h"

/**
 * create_file - Creates file.
 * @filename: A pointer to the name of the file to create.
 * @text_content: A pointer to a string to write to the file.
 *
 * Return: If the function fails - -1.
 *         Otherwise - 1.
 */
int create_file(const char *filename, char *text_content)
{
	int key = 0, fle, ik;

	if (filename == NULL)
		return (-1);

	if (text_content != NULL)
	{
		for (key = 0; text_content[key];)
			key++;
	}

	fle = open(filename, O_CREAT | O_RDWR | O_TRUNC, 0600);
	ik = write(fle, text_content, key);

	if (fle == -1 || ik == -1)
		return (-1);

	close(fle);

	return (1);
}
