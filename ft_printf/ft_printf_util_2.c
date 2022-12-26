#include <stdio.h>
#include <stdarg.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdint.h>

int print_string(char *str)
{
    int count;

    if (str)
    {
        count = 0;
        while (str[count++])
            ;
        return (write(1, str, count - 1));
    }
    else
    {
        return (write(1, "(null)", 6));
    }
}

int print_char(char c)
{
    return (write(1, &c, 1));
}

void print_int(int64_t n, int *count)
{
    if (n < 0)
    {
        *count += write(1, "-", 1);
        n = -n;
    }
    if (n >= 10)
        print_int(n / 10, count);
    *count += write(1, &"0123456789"[n % 10], 1);
}

void print_uint(uint64_t n, int *count)
{
    if (n >= 10)
        print_uint(n / 10, count);
    *count += write(1, &"0123456789"[n % 10], 1);
}

void print_hex(uint64_t n, int *count, char *charset)
{
    if (n >= 16)
    {
        print_hex(n / 16, count, charset);
    }
    *count += write(1, &charset[n % 16], 1);
}

void print_pointer(uintptr_t n, int *count)
{
    *count += write(1, "0x", 2);
    print_hex(n, count, "0123456789abcdef");
}

int format_check(const char *format, va_list args, int *count, int i)
{
    if (format[i] == 's')
        *count += print_string(va_arg(args, char*));
    else if (format[i] == 'c')
        *count += print_char(va_arg(args, int));
    else if (format[i] == 'd')
        print_int(va_arg(args, int), count);
    else if (format[i] == 'u')
        print_uint(va_arg(args, unsigned int), count);
    else if (format[i] == 'x')
        print_hex(va_arg(args, unsigned int), count, "0123456789abcdef");
    else if (format[i] == 'X')
        print_hex(va_arg(args, unsigned int), count, "0123456789ABCDEF");
    else if (format[i] == 'p')
        print_pointer(va_arg(args, uintptr_t), count);
    else if (format[i] == '%')
        *count += write(1, "%%", 1);
    else
        return (0);
    return (1);
}

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