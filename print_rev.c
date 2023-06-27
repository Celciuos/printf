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
	int i, j = 0; // <--- initialze two int vars?
	char *s = va_arg(l, char *); // <--- get character pointer containing the next argument

	(void)f; // <-- discarding f by casting it void
	
	if (!s)// <-- checks if s returned a value
		s = "(null)";//<--- returns a string for s 

	while (s[i])// <--- iterates through s
		i++;//<--- essentially counts s

	for (i = i - 1; i >= 0; i--)//<---
	{
		_putchar(s[i]);
		j++;
	}  
		


	return (j);
}

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