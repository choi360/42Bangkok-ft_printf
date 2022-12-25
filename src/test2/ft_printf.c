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

void ft_print_nbr(int64_t nbr, int base, char *base_str, int *i)
{
    if (nbr < 0)
    {
        *i += write(1, "-", 1);
        nbr = -nbr;
    }
    if (nbr >= base)
        ft_print_nbr(nbr / base, base, base_str, i);
    *i += write(1, &base_str[nbr % base], 1);
}

void ft_print_ptr(uintptr_t nbr, uintptr_t base, char *base_str, int *i)
{
    if (nbr >= base)
        ft_print_nbr(nbr / base, base, base_str, i);
    *i += write(1, &base_str[nbr % base], 1);
}

int fmt_chk(const char *fmt, va_list ap, int *i, int j)
{
    if (fmt[j] == 's')
        *i += ft_print_str(va_arg(ap, char *), 0, 1);
    else if (fmt[j] == 'c')
        *i += ft_print_str(NULL, va_arg(ap, int), 0);
    else if (fmt[j] == 'd' || fmt[j] == 'i')
        ft_print_nbr(va_arg(ap, int), 10, "0123456789", i);
    else if (fmt[j] == 'u')
        ft_print_nbr(va_arg(ap, unsigned int), 10, "0123456789", i);
    else if (fmt[j] == 'x')
        ft_print_nbr(va_arg(ap, unsigned int), 16, "0123456789abcdef", i);
    else if (fmt[j] == 'X')
        ft_print_nbr(va_arg(ap, unsigned int), 16, "0123456789ABCDEF", i);
    else if (fmt[j] == 'p')
    {
        *i += write(1, "0x", 2);
        ft_print_ptr(va_arg(ap, uintptr_t), 16, "0123456789abcdef", i);
    }
    else if (fmt[j] == '%')
        *i += write(1, "%", 1);
    else
        return (0);
    return (1);
}

int ft_printf(const char *fmt, ...)
{
    va_list ap;
    int i;
    int j;

    i = 0;
    j = 0;
    va_start(ap, fmt);
    while (fmt[j])
    {
        if (fmt[j] == '%')
        {
            j += fmt_chk(fmt, ap, &i, j + 1);
        }
        else
            i += write(1, &fmt[j], 1);
        j++;
    }
    va_end(ap);
    return (i);
}

int main(void)
{
    int i;
    int j;

    i = 42;
    j = 21;
    ft_printf("Hello World! %s %c %d %i %u %x %X %p %%\n", "Hello", 'c', i, j, i, i, i, &i);
    printf("Hello World! %s %c %d %i %u %x %X %p %%\n", "Hello", 'c', i, j, i, i, i, &i);
    return (0);
}