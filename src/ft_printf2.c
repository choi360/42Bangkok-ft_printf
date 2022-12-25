#include <stdarg.h>
#include <stdio.h>
#include <string.h>

int ft_printf(const char *format, ...)
{
    va_list args;
    int i = 0;
    int count = 0;

    va_start(args, format);

    while (format[i] != '\0')
    {
        if (format[i] == '%')
        {
            i++;
            switch (format[i])
            {
                case 'd':
                case 'i':
                {
                    int num = va_arg(args, int);
                    count += printf("%d", num);
                    break;
                }
                case 'c':
                {
                    char c = (char)va_arg(args, int);
                    count += printf("%c", c);
                    break;
                }
                case 's':
                {
                    char *str = va_arg(args, char*);
                    count += printf("%s", str);
                    break;
                }
                case '%':
                {
                    count += printf("%%");
                    break;
                }
                default:
                {
                    count += printf("%c", format[i]);
                    break;
                }
            }
        }
        else
        {
            count += printf("%c", format[i]);
        }
        i++;
    }

    va_end(args);

    return count;
}

