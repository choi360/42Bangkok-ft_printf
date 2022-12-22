#include "ft_printf.h"

int ft_print_str(char *str, char c, int flag)
{
    int i;

    if (flag == 1)
    {
        if (str == NULL)
        {
            return (write(1, "(null)", 6));
        }
        else
        {
            i = 0;
            while (str[i++])
                ;
            return (write(1, str, i - 1));
        }
    }
    else
    {
        return (write(1, &c, 1));
    }
}

void ft_print_nbr(int64_t nbr, int base, char *base_str, int i)
{
    if (n < 0)
    {
        *i += write(1, "-", 1);
        nbr = -nbr;
    }
    if (nbr >= base)
        ft_print_nbr(nbr / base, base, base_str, i);
    *i += write(1, &base_str[nbr % base], 1);
}

void ft_print_ptr(uint64_t nbr, int base, char *base_str, int i)
{
    if (nbr >= base)
        ft_print_nbr(nbr / base, base, base_str, i);
    *i += write(1, &base_str[nbr % base], 1);
}

int format_check(const char *format, va_list ap, int *i, int j)
{
    if (format[j] == 's')
        *i += ft_print_str(va_arg(ap, char *), 0, 1);
    else if (format[j] == 'c')
        *i += ft_print_str(NULL, va_arg(ap, int), 0);
    else if (format[j] == 'd' || format[j] == 'i')
        ft_print_nbr(va_arg(ap, int), 10, "0123456789", i);
    else if (format[j] == 'u')
        ft_print_nbr(va_arg(ap, unsigned int), 10, "0123456789", i);
    else if (format[j] == 'x')
        ft_print_nbr(va_arg(ap, unsigned int), 16, "0123456789abcdef", i);
    else if (format[j] == 'X')
        ft_print_nbr(va_arg(ap, unsigned int), 16, "0123456789ABCDEF", i);
    else if (format[j] == 'p')
        ft_print_ptr(va_arg(ap, unsigned long), 16, "0123456789abcdef", i);
    else if (format[j] == '%')
        *i += write(1, "%", 1);
    else
        return (0);
    return (1);
}

int ft_printf(const char *format, ...)
{
    va_list ap;
    int i;
    int j;

    i = 0;
    j = 0;
    va_start(ap, format);
    while (format[j])
    {
        if (format[j] == '%')
        {
            j++;
            if (format_check(format, ap, &i, j) == 0)
                return (-1);
        }
        else
            i += write(1, &format[j], 1);
        j++;
    }
    va_end(ap);
    return (i);
}