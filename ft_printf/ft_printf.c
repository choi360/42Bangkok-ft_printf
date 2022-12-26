#include "ft_printf.h"

int ft_printf(const char *format, ...)
{
    va_list args;
    int count = 0;
    int i = 0;
    va_start(args, format);
    while (format[i])
    {
        if (format[i] == '%')
        {
            i += format_check(format, args, &count, i + 1);
        }
        else
            count += write(1, &format[i], 1);
        i++;
    }
    va_end(args);
    return (count);
}
/*
int main(void)
{
    int i = 42;
    char *s = "Hello World!";
    char c = 'c';
    unsigned int u = 42;
    unsigned int x = 42;
    unsigned int X = 42;
    void *p = &i;
    ft_printf("printf: %s %c %d %u %x %X %p %%\n", s, c, i, u, x, X, p);
    ft_printf("printf: %s %c %d %u %x %X %p %%\n", s, c, i, u, x, X, p);
    ft_printf("printf: %s %c %d %u %x %X %p %%\n", NULL, c, i, u, x, X, p);
    ft_printf("printf: %s %c %d %u %x %X %p %%\n", s, c, i, u, x, X, NULL);
    ft_printf("printf: %s %c %d %u %x %X %p %%\n", NULL, c, i, u, x, X, NULL);
    ft_printf("printf: %s %c %d %u %x %X %p %%\n", s, c, i, u, x, X, p);
}
*/