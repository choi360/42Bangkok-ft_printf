/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_util_2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmethawa <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/27 19:15:01 by kmethawa          #+#    #+#             */
/*   Updated: 2022/12/27 19:44:30 by kmethawa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	print_hex(uint64_t n, int *count, char *charset)
{
	if (n >= 16)
	{
		print_hex(n / 16, count, charset);
	}
	*count += write(1, &charset[n % 16], 1);
}

void	print_pointer(uintptr_t n, int *count)
{
	*count += write(1, "0x", 2);
	print_hex(n, count, "0123456789abcdef");
}

int	format_check(const char *format, va_list args, int *count, int i)
{
	if (format[i] == 's')
		*count += print_string(va_arg(args, char *));
	else if (format[i] == 'c')
		*count += print_char(va_arg(args, int));
	else if (format[i] == 'd' || format[i] == 'i')
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
