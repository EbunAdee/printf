#include "main.h"

/**
 * get_size - Calculates the size to cast the argument
 * and prints it out
 * @format: Formatted string in which to print the arguments
 * @a: List of arguments to be printed.
 *
 * Return: Precision.
 */
int get_size(const char *format, int *a)
{
	int cur_a = *a + 1;
	int size = 0;

	if (format[cur_a] == 'l')
		size = S_LONG;
	else if (format[cur_a] == 't')
		size = S_SHORT;

	if (size == 0)
		*a = cur_a - 1;
	else
		*a = cur_a;

	return (size);
}
