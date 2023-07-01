#include "main.h"
#include <stdarg.h>
#include <stdio.h>

void print_buffer(char buffer[], int *buff_idx);

/**
 * _printf - Printf function
 * @format: format.
 * Return: Printed chars.
 */
int _printf(const char *format, ...)
{
	int a, printed = 0, printed_chars = 0;
	int flags, width, precision, size, buff_idx = 0;
	va_list list;
	char buffer[BUFF_SIZE];

	if (format == NULL)
		return (-1);

	va_start(list, format);

	for (a = 0; format && format[a] != '\0'; a++)
	{
		if (format[a] != '%')
		{
			buffer[buff_idx++] = format[a];
			if (buff_idx == BUFF_SIZE)
				print_buffer(buffer, &buff_idx);
			/** write(1, &format[a], 1); **/
			printed_chars++;
		}
		else
		{
			print_buffer(buffer, &buff_idx);
			flags = get_flags(format, &a);
			width = get_width(format, &a, list);
			precision = get_precision(format, &a, list);
			size = get_size(format, &a);
			++a;
			printed = handle_print(format, &a, list, buffer,
				flags, width, precision, size);
			if (printed == -1)
				return (-1);
			printed_chars += printed;
		}
	}

	print_buffer(buffer, &buff_idx);

	va_end(list);

	return (printed_chars);
}

/**
 * print_buffer - Prints the contents of the buffer if it exist
 * @buffer: Array of chars
 * @buff_idx: Index at which to add next char, represents the length.
 */
void print_buffer(char buffer[], int *buff_idx)
{
	if (*buff_idx > 0)
		write(1, &buffer[0], *buff_idx);

	*buff_idx = 0;
}
