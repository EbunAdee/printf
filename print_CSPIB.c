#include "main.h"

/************************* PRINT CHAR ****************************/

/**
 * print_char - Prints a char
 * to the standard
 * output
 * @types: List a of arguments
 * @buffer: Buffer array to handle print
 * @flags:  Calculates active flags
 * @width: Width
 * @precision: Precision specification
 * @size: Size specifier
 * Return: Number of chars printed
 */
int print_char(va_list types, char buffer[],
	int flags, int width, int precision, int size)
{
	char c = va_arg(types, int);

	return (handle_write_char(c, buffer, flags, width, precision, size));
}
/************************* PRINT A STRING *************************/
/**
 * print_string - Prints a string
 * @types: List a of arguments
 * @buffer: Buffer array to handle print
 * @flags:  Calculates active flags
 * @width: get width.
 * @precision: Precision specification
 * @size: Size specifier
 * Return: Number of chars printed
 */
int print_string(va_list types, char buffer[],
	int flags, int width, int precision, int size)
{
	int len = 0, a;
	char *str = va_arg(types, char *);

	UNUSED(buffer);
	UNUSED(flags);
	UNUSED(width);
	UNUSED(precision);
	UNUSED(size);
	if (strg == NULL)
	{
		strg = "(null)";
		if (precision >= 6)
			strg = "      ";
	}

	while (strg[len] != '\0')
		len++;

	if (precision >= 0 && precision < len)
		len = precision;

	if (width > len)
	{
		if (flags & F_SUB)
		{
			write(1, &strg[0], len);
			for (i = width - len; i > 0; a--)
				write(1, " ", 1);
			return (width);
		}
		else
		{
			for (a = width - len; a > 0; a--)
				write(1, " ", 1);
			write(1, &strg[0], len);
			return (width);
		}
	}

	return (write(1, strg, len));
}
/************************* PRINT PERCENT SIGN *************************/
/**
 * print_percent - Prints a percent sign
 * @types: Lista of arguments
 * @buffer: Buffer array to handle print
 * @flags:  Calculates active flags
 * @width: get width.
 * @precision: Precision specification
 * @size: Size specifier
 * Return: Number of chars printed
 */
int print_percent(va_list types, char buffer[],
	int flags, int width, int precision, int size)
{
	UNUSED(types);
	UNUSED(buffer);
	UNUSED(flags);
	UNUSED(width);
	UNUSED(precision);
	UNUSED(size);
	return (write(1, "%%", 1));
}

/************************* PRINT INT *************************/
/**
 * print_int - Print int
 * @types: Lista of arguments
 * @buffer: Buffer array to handle print
 * @flags:  Calculates active flags
 * @width: get width.
 * @precision: Precision specification
 * @size: Size specifier
 * Return: Number of chars printed
 */
int print_int(va_list types, char buffer[],
	int flags, int width, int precision, int size)
{
	int a = BUFF_SIZE - 2;
	int is_neg = 0;
	long int m = va_arg(types, long int);
	unsigned long int n;

	m = convert_number_size(m, size);

	if (m == 0)
		buffer[a--] = '0';

	buffer[BUFF_SIZE - 1] = '\0';
	n = (unsigned long int)m;

	if (m < 0)
	{
		n = (unsigned long int)((-1) * m);
		is_neg = 1;
	}

	while (n > 0)
	{
		buffer[a--] = (n % 10) + '0';
		n /= 10;
	}

	a++;

	return (write_number(is_neg, a, buffer, flags, width, precision, size));
}

/************************* PRINT BINARY *************************/
/**
 * print_binary - Prints an unsigned number
 * @types: Lista of arguments
 * @buffer: Buffer array to handle print
 * @flags:  Calculates active flags
 * @width: get width.
 * @precision: Precision specification
 * @size: Size specifier
 * Return: Numbers of char printed.
 */
int print_binary(va_list types, char buffer[],
	int flags, int width, int precision, int size)
{
	unsigned int x, y, a, sum;
	unsigned int b[32];
	int counter;

	UNUSED(buffer);
	UNUSED(flags);
	UNUSED(width);
	UNUSED(precision);
	UNUSED(size);

	x = va_arg(types, unsigned int);
	y = 2147483648; /* (2 ^ 31) */
	b[0] = x / y;
	for (a = 1; a < 32; a++)
	{
		y /= 2;
		b[a] = (x / y) % 2;
	}
	for (a = 0, sum = 0, counter = 0; a < 32; a++)
	{
		sum += b[a];
		if (sum || a == 31)
		{
			char z = '0' + b[a];

			write(1, &z, 1);
			counter++;
		}
	}
	return (counter);
}

