// ft_printf.c
#include <stdarg.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdint.h>

void print_char(va_list args, int *count)
{
    char c = va_arg(args, int);
    *count += write(1, &c, 1);
}

void print_string(va_list args, int *count)
{
    char *str = va_arg(args, char*);
    if (str)
    {
        *count += write(1, str, strlen(str));
    }
    else
    {
        *count += write(1, "(null)", 6);
    }
    
}

void print_int(va_list args, int *count)
{
    int64_t n = va_arg(args, int);
    if (n < 0)
    {
        *count += write(1, "-", 1);
        n = -n;
    }
    if (n >= 10)
    {
        print_int(n / 10, count);
    }
    *count += write(1, "0123456789"[n % 10], 1);
}

void print_unit(va_list args, int *count)
{
    uint64_t n = va_arg(args, unsigned int);
    if (n >= 10)
    {
        print_unit(n / 10, count);
    }
    *count += write(1, "0123456789"[n % 10], 1);
}

void print_hex(va_list args, int *count, char *charset)
{
    uint64_t n = va_arg(args, unsigned int);
    if (n >= 16)
    {
        print_hex(n / 16, count, charset);
    }
    *count += write(1, &charset[n % 16], 1);
}

void print_pointer(va_list args, int *count)
{
    uintptr_t n = va_arg(args, uintptr_t);
    *count += write(1, "0x", 2);
    if (n >= 16)
    {
        print_pointer(n / 16, count);
    }
    *count += write(1, "0123456789abcdef"[n % 16], 1);
}

// ft_printf main function
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
            i++;
            if (format[i] == 'c')
                print_char(args, &count);
            else if (format[i] == 's')
                print_string(args, &count);
            else if (format[i] == 'd')
                print_int(args, &count);
            else if (format[i] == 'u')
                print_unit(args, &count);
            else if (format[i] == 'x')
                print_hex(args, &count, "0123456789abcdef");
            else if (format[i] == 'X')
                print_hex(args, &count, "0123456789ABCDEF");
            else if (format[i] == 'p')
                print_pointer(args, &count);
        }
        else
            *count += write(1, &format[i], 1);
        i++;
    }
    va_end(args);
    return (count);
}

// main function to test ft_printf
int main(void)
{
    int i = 42;
    char *s = "Hello World!";
    ft_printf("Hello World! %c %s %d %u %x %X %p", 'A', s, i, i, i, i, &i);
    return (0);
}
