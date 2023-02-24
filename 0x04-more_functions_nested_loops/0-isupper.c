#include "main.h"
#include <stdio.h>

/**
 * _isupper - checks for uppercase character
 * code by ArchibaldTK
 * @c: the int for the parameters of my function
 * Return: 1 if c is uppercase, 0 otherwise
*/

int _isupper(int c)
{
	if (c >= 65 && c <= 90)
	{
	return (1);
	}
	else
	return (0);
}
