#include "main.h"
/**
 * handle_print_type - Prints an argument based on its type and
 * shows it on the stdout
 * @frmt: Formatted string in which to print the arguments.
 * @list: List of arguments to be printed.
 * @idx: idx.
 * @buffer: Buffer array to handle print.
 * @flags: Calculates active flags
 * @width: get width.
 * @precision: Precision specification
 * @size: Size specifier
 * Return: 1 or 2;
 */
int handle_print_type(const char *frmt, int *idx, va_list list, char buffer[],
	int flags, int width, int precision, int size)
{
	int a, unknwlen = 0, printed_chars = -1;
	frmt_t frmt_types[] = {
		{'c', print_char}, {'s', print_string}, {'%', print_percent},
		{'i', print_int}, {'d', print_int}, {'b', print_binary},
		{'u', print_unsigned_num}, {'o', print_octa},
		{'x', print_hexadecimal}, {'X', print_hexa_upper},
		{'p', print_pointer}, {'S', print_non_printable},
		{'r', print_reverse}, {'R', print_rot13string}, {'\0', NULL}};

	for (a = 0; frmt_types[a].frmt != '\0'; a++)
		if (frmt[*idx] == frmt_types[a].frmt)
			return (frmt_types[a].fcn(list, buffer, flags, width, precision, size));

	if (frmt_types[a].frmt == '\0')
	{
		if (frmt[*idx] == '\0')
			return (-1);
		unknwlen += write(1, "%%", 1);
		if (frmt[*idx - 1] == ' ')
			unknwlen += write(1, " ", 1);
		else if (width)
		{
			--(*idx);
			while (frmt[*idx] != ' ' && frmt[*idx] != '%')
				--(*idx);
			if (frmt[*idx] == ' ')
				--(*idx);
			return (1);
		}
		unknwlen += write(1, &frmt[*idx], 1);
		return (unknwlen);
	}
	return (printed_chars);
}
