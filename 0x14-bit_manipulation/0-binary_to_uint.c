#include "main.h"
#include <stdio.h>

/**
 * binary_to_uint - convert a binary number to an unsigned int
 * @b: char string
 * Return: converted decimal number or 0 if there is an unconvertable char
 */
unsigned int binary_to_uint(const char *b)
{
	int gt;
	unsigned int fy, yk;

	if (b == NULL)
		return (0);

	for (gt = 0; b[gt]; gt++)
	{
		if (b[gt] != '0' && b[gt] != '1')
			return (0);
	}

	for (yk = 1, fy = 0, gt--; gt >= 0; gt--, yk *= 2)
	{
		if (b[gt] == '1')
			fy += yk;
	}

	return (fy);
}
