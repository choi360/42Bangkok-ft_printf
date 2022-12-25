#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BUFFER_SIZE 1024

int ft_printf(const char *format, ...)
{
    va_list args;
    int i = 0;
    int j = 0;
    int k = 0;
    int printed = 0;
    int precision = 0;
    int field_width = 0;
    int base = 10;
    int is_negative = 0;
    int is_alternate = 0;
    int is_left_justified = 0;
    int is_leading_zeroes = 0;
    int is_blank = 0;
    int is_signed = 0;
    char buffer[BUFFER_SIZE];
    char *string_arg;
    char *string_output;
    long long int int_arg;

    va_start(args, format);

    while (format[i] != '\0')
    {
        if (format[i] == '%')
        {
            i++;

            // Parse flags
            while (1)
            {
                if (format[i] == '#')
                {
                    is_alternate = 1;
                }
                else if (format[i] == '0')
                {
                    is_leading_zeroes = 1;
                }
                else if (format[i] == '-')
                {
                    is_left_justified = 1;
                }
                else if (format[i] == ' ')
                {
                    is_blank = 1;
                }
                else
                {
                    break;
                }
                i++;
            }

            // Parse field width
            if (format[i] == '*')
            {
                field_width = va_arg(args, int);
                i++;
            }
            else
            {
                while (format[i] >= '0' && format[i] <= '9')
                {
                    field_width = (field_width * 10) + (format[i] - '0');
                    i++;
                }
            }

            // Parse precision
            if (format[i] == '.')
            {
                i++;

                if (format[i] == '*')
                {
                    precision = va_arg(args, int);
                    i++;
                }
                else
                {
                    while (format[i] >= '0' && format[i] <= '9')
                    {
                        precision = (precision * 10) + (format[i] - '0');
                        i++;
                    }
                }
            }

            // Parse length modifier
            if (format[i] == 'h')
            {
                i++;
                if (format[i] == 'h')
                {
                    i++;
                }
            }
            else if (format[i] == '

