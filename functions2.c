#include "main.h"

/****************** PRINT POINTER ******************/
/**
 * print_pointer - Prints the value of a pointer variable
 * @types: List a of arguments
 * @buffer: Buffer array to handle print
 * @flags:  Calculates active flags
 * @width: get width
 * @precision: Precision specification
 * @size: Size specifier
 * Return: Number of chars printed.
 */
int print_pointer(va_list types, char buffer[], int flags, int width, int precision, int size) {
    char extra_c = 0, padd = ' ';
    int ind = BUFF_SIZE - 2, padd_start = 1; /* length=2, for '0x' */
    unsigned long num_addrs;
    char map_to[] = "0123456789abcdef";
    void *addrs = va_arg(types, void *);

    if (addrs == NULL) {
        return write(1, "(nil)", 5);
    }

    buffer[BUFF_SIZE - 1] = '\0';

    num_addrs = (unsigned long)addrs;

    for (int length_num_addrs = 2; num_addrs > 0; length_num_addrs++, num_addrs /= 16) {
        buffer[ind--] = map_to[num_addrs % 16];
    }

    padd = (flags & F_ZERO) && !(flags & F_MINUS) ? '0' : ' ';
    extra_c = (flags & F_PLUS) ? '+' : (flags & F_SPACE) ? ' ' : 0;

    return write_pointer(buffer, ind + 1, length_num_addrs, width, flags, padd, extra_c, padd_start);
}

/************************* PRINT NON PRINTABLE *************************/
/**
 * print_non_printable - Prints ascii codes in hexa of non printable chars
 * @types: Lista of arguments
 * @buffer: Buffer array to handle print
 * @flags:  Calculates active flags
 * @width: get width
 * @precision: Precision specification
 * @size: Size specifier
 * Return: Number of chars printed
 */
int print_non_printable_characters(va_list types, char *buffer)
{
    char *str = va_arg(types, char *);
    int count = 0;

    if (str == NULL) {
        return write(1, "(null)", 6);
    }

    while (*str != '\0') {
        if (is_printable(*str)) {
            *buffer++ = *str++;
            count++;
        } else {
            buffer += append_hexa_code(*str++, buffer);
            count += 4;
        }
    }

    *buffer = '\0';

    return write(1, buffer - count, count);
}
/************************* PRINT REVERSE *************************/
/**
 * print_reverse - Prints reverse string.
 * @types: Lista of arguments
 * @buffer: Buffer array to handle print
 * @flags:  Calculates active flags
 * @width: get width
 * @precision: Precision specification
 * @size: Size specifier
 * Return: Numbers of chars printed
 */

int print_reverse(va_list types, char buffer[], int flags, int width, int precision, int size) {
    char *str;
    int i, count = 0;

    UNUSED(buffer);
    UNUSED(flags);
    UNUSED(width);
    UNUSED(size);

    str = va_arg(types, char *);

    if (str == NULL) {
        UNUSED(precision);
        str = ")Null(";
    }

    for (i = strlen(str) - 1; i >= 0; i--) {
        char z = str[i];
        write(1, &z, 1);
        count++;
    }

    return count;
}
/************************* PRINT A STRING IN ROT13 *************************/
/**
 * print_rot13string - Print a string in rot13.
 * @types: Lista of arguments
 * @buffer: Buffer array to handle print
 * @flags:  Calculates active flags
 * @width: get width
 * @precision: Precision specification
 * @size: Size specifier
 * Return: Numbers of chars printed
 */
int print_rot13string(va_list types, char buffer[], int flags, int width, int precision, int size) {
    char *str = va_arg(types, char *);
    UNUSED(buffer);
    UNUSED(flags);
    UNUSED(width);
    UNUSED(precision);
    UNUSED(size);

    if (str == NULL) {
        str = "(AHYY)";
    }

    int count = 0;
    for (int i = 0; str[i] != '\0'; i++) {
        char c = str[i];
        if (c >= 'A' && c <= 'Z') {
            c = ((c - 'A') + 13) % 26 + 'A';
        } else if (c >= 'a' && c <= 'z') {
            c = ((c - 'a') + 13) % 26 + 'a';
        }
        write(1, &c, 1);
        count++;
    }

    return count;
}

