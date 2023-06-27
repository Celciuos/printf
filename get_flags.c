#include "main.h"

/**
 * get_flags - Calculates active flags
 * @format: Formatted string in which to print the arguments
 * @i: take a parameter.
 * 
 * Return: Flags:
 */
int get_flags(const char *format, int *i)
{
    int curr_i = *i + 1;
    int flags = 0;

    switch (format[curr_i])
    {
        case '-':
            flags |= F_MINUS;
            curr_i++;
            break;
        case '+':
            flags |= F_PLUS;
            curr_i++;
            break;
        case '0':
            flags |= F_ZERO;
            curr_i++;
            break;
        case '#':
            flags |= F_HASH;
            curr_i++;
            break;
        case ' ':
            flags |= F_SPACE;
            curr_i++;
            break;
        default:
            break;
    }

    *i = curr_i - 1;

    return flags;
}

