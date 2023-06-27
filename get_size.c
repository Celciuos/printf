#include "main.h"

/**
 * get_size -Calculates the size to cast the argument
 * @format: Formatted string in which to print the arguments
 * @i: List of arguments to be printed.
 *
 * Return: Precision.
 */
int get_size(const char *format, int *i)
{
    int curr_i = *i + 1;
    int size = 0;

    switch (format[curr_i])
    {
        case 'l':
            size = S_LONG;
            break;
        case 'h':
            size = S_SHORT;
            break;
        default:
            *i = curr_i - 1;
            break;
    }

    *i = curr_i;
    return size;
}
