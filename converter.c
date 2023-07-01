#include "main.h"

/**
 * _printable - Evaluates if a char is printable
 * @c: Char to be evaluated.
 * utilities
 * Return: 1 if c is printable, 0 otherwise
 */
int _printable(char c)
{
	if (c >= 32 && c < 127)
		return (1);

	return (0);
}

/**
 * append_hexa_code - Append ascci in hexadecimal code to buffer
 * @buffer: Array of chars.
 * @a: Index at which to start appending.
 * @ascii_cod: ASSCI CODE.
 * Return: Always 3
 */
int apend_hexa_cod(char ascii_cod, char buffer[], int a)
{
	char map_it[] = "0123456789ABCDEF";
	/* The hexa format code is always 2 digits long */
	if (ascii_cod < 0)
		ascii_cod *= -1;

	buffer[a++] = '\\';
	buffer[a++] = 'x';

	buffer[a++] = map_it[ascii_cod / 16];
	buffer[a] = map_it[ascii_cod % 16];

	return (3);
}

/**
 * is_a_digit - Verifies if a char is a digit
 * @c: Char to be evaluated
 *
 * Return: 1 if c is a digit, 0 otherwise
 */
int is_a_digit(char c)
{
	if (c >= '0' && c <= '9')
		return (1);

	return (0);
}

/**
 * convert_number_size - Casts a number to the specified size
 * @n: Number to be casted.
 * @size: Number indicating the type to be casted.
 *
 * Return: Casted value of num
 */
long int convert_number_size(long int n, int size)
{
	if (size == S_LONG)
		return (n);
	else if (size == S_SHORT)
		return ((short)n);

	return ((int)n);
}

/**
 * convert_size_unsignd - Casts a number to the specified size
 * @n: Number to be casted
 * @size: Number indicating the type to be casted
 *
 * Return: Casted value of num
 */
long int convert_size_unsignd(unsigned long int n, int size)
{
	if (size == S_LONG)
		return (n);
	else if (size == S_SHORT)
		return ((unsigned short)n);

	return ((unsigned int)n);
}
