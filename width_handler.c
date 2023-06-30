#include "main.h"

/**
 * get_width - Calculates the width for printing
 * and returns the result
 * @format: Formatted string in which to print the arguments.
 * @a: List of arguments to be printed.
 * @list: list of arguments.
 *
 * Return: width.
 */
int get_width(const char *format, int *a, va_list list)
{
	int cur_a;
	int width = 0;

	for (cur_a = *a + 1; format[cur_a] != '\0'; cur_a++)
	{
		if (is_a_digit(format[cur_a]))
		{
			width *= 10;
			width += format[cur_a] - '0';
		}
		else if (format[cur_a] == '*')
		{
			cur_a++;
			width = va_arg(list, int);
			break;
		}
		else
			break;
	}

	*a = cur_a - 1;

	return (width);
}

