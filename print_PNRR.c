#include "main.h"

/******* PRINT POINTER *******/
/**
 * print_pointer - Prints the value of a pointer variable
 * to the
 * standard output
 * @types: List a of arguments
 * @buffer: Buffer array to handle print
 * @flags:  Calculates active flags
 * @width: get width
 * @precision: Precision specification
 * @size: Size specifier
 * Return: Number of chars printed.
 */
int print_pointer(va_list types, char buffer[],
	int flags, int width, int precision, int size)
{
	char another_c = 0, pad = ' ';
	int idx = BUFF_SIZE - 2, len = 2, pad_strt = 1; /* len=2, for '0x' */
	unsigned long num_adrs;
	char map_it[] = "0123456789abcdef";
	void *adrs = va_arg(types, void *);

	UNUSED(width);
	UNUSED(size);

	if (adrs == NULL)
		return (write(1, "(nil)", 5));

	buffer[BUFF_SIZE - 1] = '\0';
	UNUSED(precision);

	num_adrs = (unsigned long)adrs;

	while (num_adrs > 0)
	{
		buffer[idx--] = map_it[num_adrs % 16];
		num_adrs /= 16;
		len++;
	}

	if ((flags & F_ZERO) && !(flags & F_SUB))
		pad = '0';
	if (flags & F_PLUS)
		another_c = '+', len++;
	else if (flags & F_SPACE)
		another_c = ' ', len++;

	idx++;

	/*return (write(1, &buffer[a], BUFF_SIZE - a - 1));*/
	return (write_pointer(buffer, ind, len,
		width, flags, pad, another_c, pad_strt));
}

/********* PRINT NON PRINTABLE *********/
/**
 * print_non_printable - Prints ascii codes in hexa of non printable chars
 * @types: Lista of arguments
 * @buffer: Buffer array to handle print
 * @flags:  Calculates active flags
 * @width: get width
 * @precision: Precision specification
 * @size: Size specifier
 * Return: Number of chars printed
 */
int print_non_printable(va_list types, char buffer[],
	int flags, int width, int precision, int size)
{
	int a = 0, init = 0;
	char *strg = va_arg(types, char *);

	UNUSED(flags);
	UNUSED(width);
	UNUSED(precision);
	UNUSED(size);

	if (strg == NULL)
		return (write(1, "(null)", 6));

	while (strg[a] != '\0')
	{
		if (_printable(strg[a]))
			buffer[a + init] = strg[a];
		else
			init += apend_hexa_cod(strg[a], buffer, a + init);

		a++;
	}

	buffer[a + init] = '\0';

	return (write(1, buffer, a + init));
}

/********* PRINT REVERSE *********/
/**
 * print_reverse - Prints reverse string.
 * @types: Lista of arguments
 * @buffer: Buffer array to handle print
 * @flags:  Calculates active flags
 * @width: get width
 * @precision: Precision specification
 * @size: Size specifier
 * Return: Numbers of chars printed
 */

int print_reverse(va_list types, char buffer[],
	int flags, int width, int precision, int size)
{
	char *strg;
	int a, counter = 0;

	UNUSED(buffer);
	UNUSED(flags);
	UNUSED(width);
	UNUSED(size);

	strg = va_arg(types, char *);

	if (strg == NULL)
	{
		UNUSED(precision);

		strg = ")Null(";
	}
	for (a = 0; strg[a]; a++)
		;

	for (a = a - 1; a >= 0; a--)
	{
		char z = strg[a];

		write(1, &z, 1);
		counter++;
	}
	return (counter);
}
/********* PRINT A STRING IN ROT13 *********/
/**
 * print_rot13string - Print a string in rot13.
 * @types: List all  arguments
 * @buffer: Buffer array to handle print
 * @flags:  Calculates active flags
 * @width: get width
 * @precision: Precision specification
 * @size: Size specifier
 * Return: Numbers of chars printed
 */
int print_rot13string(va_list types, char buffer[],
	int flags, int width, int precision, int size)
{
	char y;
	char *strg;
	unsigned int a, b;
	int counter = 0;
	char input[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";
	char output[] = "NOPQRSTUVWXYZABCDEFGHIJKLMnopqrstuvwxyzabcdefghijklm";

	strg = va_arg(types, char *);
	UNUSED(buffer);
	UNUSED(flags);
	UNUSED(width);
	UNUSED(precision);
	UNUSED(size);

	if (strg == NULL)
		strg = "(AHYY)";
	for (a = 0; strg[a]; a++)
	{
		for (b = 0; input[b]; b++)
		{
			if (input[b] == strg[a])
			{
				y = output[b];
				write(1, &y, 1);
				counter++;
				break;
			}
		}
		if (!input[b])
		{
			y = strg[a];
			write(1, &y, 1);
			counter++;
		}
	}
	return (counter);
}
