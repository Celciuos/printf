#include "main.h"

void print_buffer(char buffer[], int *buff_ind);

/**
 * _printf - Printf function
 * @format: format.
 * Return: Printed chars.
 */
int _printf(const char *format, ...)
{
    int printed_chars = 0, buff_ind = 0;
    va_list list;
    char buffer[BUFF_SIZE];

    if (format == NULL)
        return (-1);

    va_start(list, format);

    while (*format)
    {
        if (*format != '%')
        {
            buffer[buff_ind++] = *format;
            if (buff_ind == BUFF_SIZE)
                printed_chars += print_buffer(buffer, &buff_ind);
            else
                printed_chars++;
        }
        else
        {
            printed_chars += print_buffer(buffer, &buff_ind);
            format = handle_format(format + 1, &list, &printed_chars);
            if (format == NULL)
                return (-1);
        }
        format++;
    }

    printed_chars += print_buffer(buffer, &buff_ind);
    va_end(list);

    return (printed_chars);
}

/**
 * print_buffer - Prints the contents of the buffer if it exist
 * @buffer: Array of chars
 * @buff_ind: Index at which to add next char, represents the length.
 */
void print_buffer(char buffer[], int *buff_ind)
{
	if (*buff_ind > 0)
		write(1, &buffer[0], *buff_ind);

	*buff_ind = 0;
}
