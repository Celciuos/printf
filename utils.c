#include "main.h"

/**
 * is_printable - Evaluates if a char is printable
 * @c: Char to be evaluated.
 *
 * Return: 1 if c is printable, 0 otherwise
 */
int is_printable(char c)
{
    int printable = 0;
    if (c >= 32 && c < 127)
    {
        printable = 1;
    }
    return printable;
}


/**
 * append_hexa_code - Append ascci in hexadecimal code to buffer
 * @buffer: Array of chars.
 * @i: Index at which to start appending.
 * @ascii_code: ASSCI CODE.
 *
 * Return: Always 3
 */
int append_hexa_code(char ascii_code, char buffer[], int i)
{
    const char map_to[] = "0123456789ABCDEF";
    const int HEXA_CODE_LENGTH = 2;
    const int HEXA_BASE = 16;
    const int ASCII_CODE_ABS = abs(ascii_code);

    buffer[i++] = '\\';
    buffer[i++] = 'x';

    buffer[i++] = map_to[ASCII_CODE_ABS / HEXA_BASE];
    buffer[i] = map_to[ASCII_CODE_ABS % HEXA_BASE];

    return HEXA_CODE_LENGTH + 1;
}


/**
 * is_digit - Verifies if a char is a digit
 * @c: Char to be evaluated
 *
 * Return: 1 if c is a digit, 0 otherwise
 */
int is_digit(char c)
{
    return (c >= '0' && c <= '9');
}


/**
 * convert_size_number - Casts a number to the specified size
 * @num: Number to be casted.
 * @size: Number indicating the type to be casted.
 *
 * Return: Casted value of num
 */
long int convert_size_number(long int num, int size)
{
    switch(size)
    {
        case S_LONG:
            return num;
        case S_SHORT:
            return (short)num;
        default:
            return (int)num;
    }
}


/**
 * convert_size_unsgnd - Casts a number to the specified size
 * @num: Number to be casted
 * @size: Number indicating the type to be casted
 *
 * Return: Casted value of num
 */
long int convert_size_unsgnd(unsigned long int num, int size)
{
    switch(size)
    {
        case S_LONG:
            return num;
        case S_SHORT:
            return (unsigned short)num;
        default:
            return (unsigned int)num;
    }
}
