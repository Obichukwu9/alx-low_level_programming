#include "main.h"

/**
 * clear_bit - Sets the value of a bit at a given index to 0.
 * @n: pointer to the bit.
 * @index:  index to set the value to  0.
 *
 * return: -1 0r 1.
 */
int clear_bit(unsigned long int *n, unsigned int index)
{
	if (index > 64)
		return (-1);

	*n &= ~(1 << index);

	return (1);
}
