#include <stdarg.h>
#include <stdio.h>
#include "main.h"
/**
 * print_rev - prints a string in reverse
 * @l: argument from _printf
 * @f: pointer to the struct flags that determines
 * if a flag is passed to _printf
 * Return: length of the printed string
 */
int print_rev(va_list l, flags_t *f)
{
	int i, j = 0;
	char *s = va_arg(l, char *);

	(void)f;
	
	if (!s)
		s = "(null)";

	while (s[i])
		i++;

	for (i = i - 1; i >= 0; i--)
	{
		_putchar(s[i]);
		j++;
	}  
		


	return (j);
}

/*
int print_reverse(va_list types,int precision)
{
	int i, count = 0;// <-- initialize two int vars
	char *str;// <--- create a string pointer


	str = va_arg(types, char *); // <--- give the pointer the address of the next variable

	if (str == NULL)// <--- checks if che next variable actually exists
	{
		UNUSED(precision);// <--- discards precision if it dosent exist

		str = ")Null(";// <--- ties the str variable to a value
	}
	for (i = 0; str[i]; i++)// <---counts all variables in string saving it to i
		;

	for (i = i - 1; i >= 0; i--)// <--- counts in reverse from last to first variable in string
	{
		char z = str[i];// <--- creates z which is the character at the current counting position i of str

		write(1, &z, 1);// <--- prints out z
		count++;// <--- Adds to count
	}
	return (count); //<--- returns count which is the actual number of characters printed to stdout
}
*/