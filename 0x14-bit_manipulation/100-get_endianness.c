#include "main.h"

/**
 * get_endianness - checks the endianness
 * Description: a function that checks the endianness
 *
 * Return: 0 if big endian, 1 if little endian
 */
int get_endianness(void)
{
	u_int32_t bbb = 0x12345678;
	u_int8_t *mmm = (u_int8_t *) &bbb;

	if (*mmm == 0x78)
	{
		return (1);
	}
	else
		return (0);
}
