#include "main.h"

/**
 * flip_bits - the  bits you would need to flip
 * to get from one number to another
 * @n: the parameter
 * @m: destiny
 *
 * Return: nflips
 */
unsigned int flip_bits(unsigned long int n, unsigned long int m)
{
	unsigned long int xor, bits = 0;

	for (xor = n ^ m; xor > 0; xor >>= 1)
	{
		bits += (xor & 1);
	}

	return (bits);
}
