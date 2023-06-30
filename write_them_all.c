#include "main.h"

/************************* WRITE HANDLE *************************/
/**
 * handle_write_char - Prints a string
 * to the stdout
 * @c: char types.
 * @buffer: Buffer array to handle print
 * @flags:  Calculates active flags.
 * @width: get width.
 * @precision: precision specifier
 * @size: Size specifier
 *
 * Return: Number of chars printed.
 */
int handle_write_char(char c, char buffer[],
	int flags, int width, int precision, int size)
{
/* char is stored at left and pad idx at buffer's right */
	int a = 0;
	char pad = ' ';

	UNUSED(precision);
	UNUSED(size);

	if (flags & F_ZERO)
		pad = '0';

	buffer[a++] = c;
	buffer[a] = '\0';

	if (width > 1)
	{
		buffer[BUFF_SIZE - 1] = '\0';
		for (a = 0; a < width - 1; a++)
			buffer[BUFF_SIZE - a - 2] = pad;

		if (flags & F_SUB)
			return (write(1, &buffer[0], 1) +
					write(1, &buffer[BUFF_SIZE - a - 1], width - 1));
		else
			return (write(1, &buffer[BUFF_SIZE - a - 1], width - 1) +
					write(1, &buffer[0], 1));
	}

	return (write(1, &buffer[0], 1));
}

/************************* WRITE NUMBER *************************/
/**
 * write_number - Prints a string
 * @is_neg: Lista of arguments
 * @idx: char types.
 * @buffer: Buffer array to handle print
 * @flags:  Calculates active flags
 * @width: get width.
 * @precision: precision specifier
 * @size: Size specifier
 *
 * Return: Number of chars printed.
 */
int write_number(int is_neg, int idx, char buffer[],
	int flags, int width, int precision, int size)
{
	int len = BUFF_SIZE - idx - 1;
	char pad = ' ', another_ac = 0;

	UNUSED(size);

	if ((flags & F_ZERO) && !(flags & F_SUB))
		pad = '0';
	if (is_neg)
		another_ac = '-';
	else if (flags & F_PLUS)
		another_ac = '+';
	else if (flags & F_SPACE)
		another_ac = ' ';

	return (write_num(idx, buffer, flags, width, precision,
		len, pad, another_ac));
}

/**
 * write_num - Write a number using a bufffer
 * @idx: Index at which the number starts on the buffer
 * @buffer: Buffer
 * @flags: Flags
 * @width: width
 * @precison: Precision specifier
 * @len: Number length
 * @pad: Pading char
 * @another_c: Extra char
 *
 * Return: Number of printed chars.
 */
int write_num(int idx, char buffer[],
	int flags, int width, int precison,
	int len, char pad, char another_c)
{
	int a, pad_strt = 1;

	if (precison == 0 && idx == BUFF_SIZE - 2 && buffer[idx] == '0' && width == 0)
		return (0); /* printf(".0d", 0)  no char is printed */
	if (precison == 0 && idx == BUFF_SIZE - 2 && buffer[idx] == '0')
		buffer[idx] = pad = ' '; /* width is displayed with padding ' ' */
	if (precison > 0 && precison < len)
		pad = ' ';
	while (precison > len)
		buffer[--idx] = '0', len++;
	if (another_c != 0)
		len++;
	if (width > len)
	{
		for (a = 1; a < width - len + 1; a++)
			buffer[a] = pad;
		buffer[a] = '\0';
		if (flags & F_SUB && pad == ' ')/* Assign extra char to left of buffer */
		{
			if (another_c)
				buffer[--idx] = another_c;
			return (write(1, &buffer[idx], len) + write(1, &buffer[1], a - 1));
		}
		else if (!(flags & F_SUB) && pad == ' ')/* extra char to left of buff */
		{
			if (another_c)
				buffer[--idx] = another_c;
			return (write(1, &buffer[1], a - 1) + write(1, &buffer[idx], len));
		}
		else if (!(flags & F_SUB) && pad == '0')/* extra char to left of pad */
		{
			if (another_c)
				buffer[--pad_strt] = another_c;
			return (write(1, &buffer[pad_strt], a - pad_strt) +
				write(1, &buffer[idx], len - (1 - pad_strt)));
		}
	}
	if (another_c)
		buffer[--idx] = another_c;
	return (write(1, &buffer[idx], len));
}

/**
 * write_unsigned - Writes an unsigned number
 * @is_neg: Number indicating if the num is negative
 * @idx: Index at which the number starts in the buffer
 * @buffer: Array of chars
 * @flags: Flags specifiers
 * @width: Width specifier
 * @precision: Precision specifier
 * @size: Size specifier
 *
 * Return: Number of written chars.
 */
int write_unsigned(int is_neg, int idx,
	char buffer[],
	int flags, int width, int precision, int size)
{
	/* The number is stored at the bufer's right and starts at position i */
	int len = BUFF_SIZE - idx - 1, a = 0;
	char pad = ' ';

	UNUSED(is_neg);
	UNUSED(size);

	if (precision == 0 && idx == BUFF_SIZE - 2 && buffer[idx] == '0')
		return (0); /* printf(".0d", 0)  no char is printed */

	if (precision > 0 && precision < len)
		pad = ' ';

	while (precision > len)
	{
		buffer[--idx] = '0';
		len++;
	}

	if ((flags & F_ZERO) && !(flags & F_SUB))
		pad = '0';

	if (width > len)
	{
		for (a = 0; a < width - len; a++)
			buffer[a] = pad;

		buffer[a] = '\0';

		if (flags & F_SUB) /* Asign extra char to left of buffer [buffer>pad]*/
		{
			return (write(1, &buffer[idx], len) + write(1, &buffer[0], i));
		}
		else /* Asign extra char to left of padding [pad>buffer]*/
		{
			return (write(1, &buffer[0], a) + write(1, &buffer[idx], len));
		}
	}

	return (write(1, &buffer[idx], len));
}

/**
 * write_pointer - Write a memory address
 * @buffer: Arrays of chars
 * @idx: Index at which the number starts in the buffer
 * @len: Length of number
 * @width: Wwidth specifier
 * @flags: Flags specifier
 * @pad: Char representing the padding
 * @another_c: Char representing extra char
 * @pad_strt: Index at which padding should start
 *
 * Return: Number of written chars.
 */
int write_pointer(char buffer[], int idx, int len,
	int width, int flags, char pad, char another_c, int pad_strt)
{
	int a;

	if (width > len)
	{
		for (a = 3; a < width - len + 3; a++)
			buffer[a] = pad;
		buffer[a] = '\0';
		if (flags & F_SUB && pad == ' ')/* Assign extra char to left of buffer */
		{
			buffer[--idx] = 'x';
			buffer[--idx] = '0';
			if (another_c)
				buffer[--idx] = another_c;
			return (write(1, &buffer[idx], len) + write(1, &buffer[3], a - 3));
		}
		else if (!(flags & F_SUB) && pad == ' ')/* extra char to left of buffer */
		{
			buffer[--idx] = 'x';
			buffer[--idx] = '0';
			if (another_c)
				buffer[--idx] = another_c;
			return (write(1, &buffer[3], a - 3) + write(1, &buffer[idx], len));
		}
		else if (!(flags & F_SUB) && pad == '0')/* extra char to left of padd */
		{
			if (another_c)
				buffer[--pad_strt] = another_c;
			buffer[1] = '0';
			buffer[2] = 'x';
			return (write(1, &buffer[pad_strt], i - pad_strt) +
				write(1, &buffer[idx], len - (1 - pad_strt) - 2));
		}
	}
	buffer[--idx] = 'x';
	buffer[--idx] = '0';
	if (another_c)
		buffer[--idx] = another_c;
	return (write(1, &buffer[idx], BUFF_SIZE - idx - 1));
}
