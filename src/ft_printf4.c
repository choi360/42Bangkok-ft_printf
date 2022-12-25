#include <stdarg.h>
#include <unistd.h>

int ft_printf(const char *format, ...)
{
    va_list args;
    int count = 0;

    va_start(args, format);

    for (int i = 0; format[i] != '\0'; i++)
    {
        if (format[i] == '%')
        {
            i++;
            switch (format[i])
            {
                case 'c':
                    count += write(1, &va_arg(args, int), 1);
                    break;
                case 's':
                    count += write(1, va_arg(args, char*), strlen(va_arg(args, char*)));
                    break;
                case 'd':
                case 'i':
                    count += write(1, "TODO", 4);
                    break;
                case 'x':
                    count += write(1, "TODO", 4);
                    break;
                case 'X':
                    count += write(1, "TODO", 4);
                    break;
                case 'u':
                    count += write(1, "TODO", 4);
                    break;
                case 'p':
                    count += write(1, "TODO", 4);
                    break;
                case '%':
                    count += write(1, "%", 1);
                    break;
                default:
                    count += write(1, "TODO", 4);
                    break;
            }
        }
        else
        {
            count += write(1, &format[i], 1);
        }
    }

    va_end(args);

    return count;
}

