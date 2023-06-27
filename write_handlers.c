#include "main.h"

/************************* WRITE HANDLE *************************/
/**
 * handle_write_char - Prints a string
 * @c: char types.
 * @buffer: Buffer array to handle print
 * @flags:  Calculates active flags.
 * @width: get width.
 * @precision: precision specifier
 * @size: Size specifier
 *
 * Return: Number of chars printed.
 */
int handle_write_char(char c, char buffer[], int flags, int width, int precision, int size)
{
    int i = 0;
    char padd = ' ';

    UNUSED(precision);
    UNUSED(size);

    if (flags & F_ZERO)
        padd = '0';

    buffer[i++] = c;
    buffer[i] = '\0';

    if (width > 1)
    {
        buffer[BUFF_SIZE - 1] = '\0';
        for (i = 0; i < width - 1; i++)
            buffer[BUFF_SIZE - i - 2] = padd;

        if (flags & F_MINUS)
            return (write(1, &buffer[0], 1) + write(1, &buffer[BUFF_SIZE - i - 1], width - 1));
        else
            return (write(1, &buffer[BUFF_SIZE - i - 1], width - 1) + write(1, &buffer[0], 1));
    }

    return (write(1, &buffer[0], 1));
}


/************************* WRITE NUMBER *************************/
/**
 * write_number - Prints a string
 * @is_negative: Lista of arguments
 * @ind: char types.
 * @buffer: Buffer array to handle print
 * @flags:  Calculates active flags
 * @width: get width.
 * @precision: precision specifier
 * @size: Size specifier
 *
 * Return: Number of chars printed.
 */
int write_number(int is_negative, int ind, char buffer[], int flags, int width, int precision, int size) {
    int length = BUFF_SIZE - ind - 1;
    char padd = ' ', extra_ch = 0;

    UNUSED(size);

    if ((flags & F_ZERO) && !(flags & F_MINUS)) {
        padd = '0';
    }
    if (is_negative) {
        extra_ch = '-';
    } else if (flags & F_PLUS) {
        extra_ch = '+';
    } else if (flags & F_SPACE) {
        extra_ch = ' ';
    }

    return write_num(ind, buffer, flags, width, precision, length, padd, extra_ch);
}


/**
 * write_num - Write a number using a bufffer
 * @ind: Index at which the number starts on the buffer
 * @buffer: Buffer
 * @flags: Flags
 * @width: width
 * @prec: Precision specifier
 * @length: Number length
 * @padd: Pading char
 * @extra_c: Extra char
 *
 * Return: Number of printed chars.
 */
int write_num(int ind, char buffer[], int flags, int width, int prec, int length, char padd, char extra_c) {
    int i, padd_start = 1;

    if (prec == 0 && ind == BUFF_SIZE - 2 && buffer[ind] == '0' && width == 0) {
        return 0; // printf(".0d", 0)  no char is printed
    }
    if (prec == 0 && ind == BUFF_SIZE - 2 && buffer[ind] == '0') {
        buffer[ind] = padd = ' '; // width is displayed with padding ' '
    }
    while (prec > length) {
        buffer[--ind] = '0';
        length++;
    }
    if (extra_c != 0) {
        length++;
    }
    if (width > length) {
        for (i = 1; i < width - length + 1; i++) {
            buffer[i] = padd;
        }
        buffer[i] = '\0';
        if (flags & F_MINUS && padd == ' ') { // Assign extra char to left of buffer
            if (extra_c) {
                buffer[--ind] = extra_c;
            }
            return write(1, &buffer[ind], length) + write(1, &buffer[1], i - 1);
        } else if (!(flags & F_MINUS) && padd == ' ') { // Extra char to left of buff
            if (extra_c) {
                buffer[--ind] = extra_c;
            }
            return write(1, &buffer[1], i - 1) + write(1, &buffer[ind], length);
        } else if (!(flags & F_MINUS) && padd == '0') { // Extra char to left of padd
            if (extra_c) {
                buffer[--padd_start] = extra_c;
            }
            return write(1, &buffer[padd_start], i - padd_start) + write(1, &buffer[ind], length - (1 - padd_start));
        }
    }
    if (extra_c) {
        buffer[--ind] = extra_c;
    }
    return write(1, &buffer[ind], length);
}


/**
 * write_unsgnd - Writes an unsigned number
 * @is_negative: Number indicating if the num is negative
 * @ind: Index at which the number starts in the buffer
 * @buffer: Array of chars
 * @flags: Flags specifiers
 * @width: Width specifier
 * @precision: Precision specifier
 * @size: Size specifier
 *
 * Return: Number of written chars.
 */
int write_unsigned(int is_negative, int ind, char buffer[], int flags, int width, int precision, int size)
{
    int length = BUFF_SIZE - ind - 1, i = 0;
    char padd = ' ';

    UNUSED(is_negative);
    UNUSED(size);

    if (precision == 0 && ind == BUFF_SIZE - 2 && buffer[ind] == '0')
        return (0);

    if (precision > 0 && precision < length)
        padd = ' ';

    while (precision > length)
    {
        buffer[--ind] = '0';
        length++;
    }

    if ((flags & F_ZERO) && !(flags & F_MINUS))
        padd = '0';

    if (width > length)
    {
        for (i = 0; i < width - length; i++)
            buffer[i] = padd;

        buffer[i] = '\0';

        if (flags & F_MINUS)
            return (write(1, &buffer[ind], length) + write(1, &buffer[0], i));
        else
            return (write(1, &buffer[0], i) + write(1, &buffer[ind], length));
    }

    return (write(1, &buffer[ind], length));
}


/**
 * write_pointer - Write a memory address
 * @buffer: Arrays of chars
 * @ind: Index at which the number starts in the buffer
 * @length: Length of number
 * @width: Wwidth specifier
 * @flags: Flags specifier
 * @padd: Char representing the padding
 * @extra_c: Char representing extra char
 * @padd_start: Index at which padding should start
 *
 * Return: Number of written chars.
 */
int write_pointer(char buffer[], int ind, int length, int width, int flags, char padd, char extra_c, int padd_start) {
    int i;
    int extra_chars = 0;
    int padding_chars = 0;
    int total_chars = length + 2;
    int buffer_start = ind - total_chars + 1;

    if (width > total_chars) {
        padding_chars = width - total_chars;
        if (flags & F_MINUS && padd == ' ') {
            buffer[ind--] = 'x';
            buffer[ind--] = '0';
            if (extra_c) buffer[ind--] = extra_c;
            extra_chars = write(1, &buffer[ind + 1], total_chars);
            for (i = 0; i < padding_chars; i++) write(1, &padd, 1);
            return extra_chars + padding_chars;
        }
        else if (!(flags & F_MINUS) && padd == ' ') {
            buffer[ind--] = 'x';
            buffer[ind--] = '0';
            if (extra_c) buffer[ind--] = extra_c;
            for (i = 0; i < padding_chars; i++) write(1, &padd, 1);
            extra_chars = write(1, &buffer[ind + 1], total_chars);
            return extra_chars + padding_chars;
        }
        else if (!(flags & F_MINUS) && padd == '0') {
            if (extra_c) buffer[--padd_start] = extra_c;
            buffer[ind--] = padd;
            buffer[ind--] = padd;
            buffer[ind--] = 'x';
            buffer[ind--] = '0';
            extra_chars = write(1, &buffer[padd_start], total_chars);
            return extra_chars + padding_chars;
        }
    }
    buffer[ind--] = 'x';
    buffer[ind--] = '0';
    if (extra_c) buffer[ind--] = extra_c;
    return write(1, &buffer[ind + 1], total_chars);
}

