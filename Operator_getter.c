#include "main.h"

/**
 * get_flags - Calculates active flags
 * @format: Formatted string in which to print the arguments
 * @a: take a parameter.
 * Return: Flags:
 */
int get_flags(const char *format, int *a)
{
	/* - + 0 # ' ' */
	/* 1 2 4 8  16 */
	int b, cur_a;
	int flags = 0;
	const char FLAGS_CHAR[] = {'-', '+', '0', '#', ' ', '\0'};
	const int FLAGS_ARR[] = {F_SUB, F_PLUS, F_ZERO, F_HASH, F_SPACE, 0};

	for (cur_a = *a + 1; format[curr_a] != '\0'; curr_a++)
	{
		for (b = 0; FLAGS_CHAR[b] != '\0'; b++)
			if (format[cur_a] == FLAGS_CHAR[b])
			{
				flags |= FLAGS_ARR[b];
				break;
			}

		if (FLAGS_CHAR[b] == 0)
			break;
	}

	*a = cur_a - 1;

	return (flags);
}

