#include "main.h"

/**
 * get_precision - Calculates the precision for printing and returns the
 * result to the stdout
 * @format: Formatted string in which to print the arguments
 * @a: List of arguments to be printed.
 * @list: list of arguments.
 *
 * Return: Precision.
 */
int get_precision(const char *format, int *a, va_list list)
{
	int cur_a = *a + 1;
	int precision = -1;

	if (format[cur_a] != '.')
		return (precision);

	precision = 0;

	for (cur_a += 1; format[cur_a] != '\0'; cur_a++)
	{
		if (is_a_digit(format[cur_a]))
		{
			precision *= 10;
			precision += format[cur_a] - '0';
		}
		else if (format[cur_a] == '*')
		{
			cur_a++;
			precision = va_arg(list, int);
			break;
		}
		else
			break;
	}

	*a = cur_a - 1;

	return (precision);
}
