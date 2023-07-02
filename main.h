#ifndef MAIN_H
#define MAIN_H
#include <stdarg.h>
#include <stdio.h>
#include <unistd.h>

#define UNUSED(x) (void)(x)
#define BUFF_SIZE 1024

/* FLAGS */
#define F_SUB 1
#define F_PLUS 2
#define F_ZERO 4
#define F_HASH 8
#define F_SPACE 16

/* SIZES */
#define S_LONG 2
#define S_SHORT 1

/**
 * struct frmt - Struct op
 * struct defination
 * @frmt: The format.
 * @fcn: The function associated.
 */
struct frmt
{
	char frmt;
	int (*fcn)(va_list, char[], int, int, int, int);
};


/**
 * typedef struct frmt frmt_t - Struct op
 * typedefination
 * @frmt: The format.
 * @frmt_t: The function associated.
 */
typedef struct frmt frmt_t;

int _printf(const char *format, ...);
int handle_print_type(const char *frmt, int *a,
va_list list, char buffer[], int flags, int width, int precision, int size);

/********************* FUNCTIONS *********************/

/* Funtions to print chars and strings */
int print_char(va_list types, char buffer[],
		int flags, int width, int precision, int size);
int print_string(va_list types, char buffer[],
		int flags, int width, int precision, int size);
int print_percent(va_list types, char buffer[],
		int flags, int width, int precision, int size);

/* Functions to print numbers */
int print_int(va_list types, char buffer[],
		int flags, int width, int precision, int size);
int print_binary(va_list types, char buffer[],
		int flags, int width, int precision, int size);
int print_unsigned_num(va_list types, char buffer[],
		int flags, int width, int precision, int size);
int print_octa(va_list types, char buffer[],
		int flags, int width, int precision, int size);
int print_hexadecimal(va_list types, char buffer[],
		int flags, int width, int precision, int size);
int print_hexa_upper(va_list types, char buffer[],
		int flags, int width, int precision, int size);

int print_hexa(va_list types, char map_it[],
char buffer[], int flags, char flag_ac, int width, int precision, int size);

/* Function to print non printable characters */
int print_non_printable(va_list types, char buffer[],
		int flags, int width, int precision, int size);

/* Funcion to print memory address */
int print_pointer(va_list types, char buffer[],
		int flags, int width, int precision, int size);

/* Funciotns to handle other specifiers */
int get_flags(const char *format, int *a);
int get_width(const char *format, int *a, va_list list);
int get_precision(const char *format, int *a, va_list list);
int get_size(const char *format, int *a);

/* Function to print string in reverse */
int print_reverse(va_list types, char buffer[],
		int flags, int width, int precision, int size);

/*Function to print a string in rot 13*/
int print_rot13string(va_list types, char buffer[],
		int flags, int width, int precision, int size);

/* width handler */
int handle_write_char(char c, char buffer[],
		int flags, int width, int precision, int size);
int write_number(int is_positive, int idx, char buffer[],
		int flags, int width, int precision, int size);
int write_num(int idx, char bff[], int flags, 
		int width, int precision,int len, char pad, char another_c);
int write_pointer(char buffer[], int idx, int len,
		int width, int flags, char pad, char another_c, int pad_strt);

int write_unsignd(int is_neg, int idx,char buffer[],
		int flags, int width, int precision, int size);

/****************** UTILS ******************/
int _printable(char);
int apend_hexa_cod(char, char[], int);
int is_a_digit(char);

long int convert_number_size(long int num, int size);
long int convert_size_unsignd(unsigned long int num, int size);

#endif /* MAIN_H */
