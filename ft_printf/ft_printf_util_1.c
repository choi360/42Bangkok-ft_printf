/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_util_1.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmethawa <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/27 19:01:23 by kmethawa          #+#    #+#             */
/*   Updated: 2022/12/27 19:14:34 by kmethawa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	print_string(char *str)
{
	int	count;

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

int	print_char(char c)
{
	return (write(1, &c, 1));
}

void	print_int(int64_t n, int *count)
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

void	print_uint(uint64_t n, int *count)
{
	if (n >= 10)
		print_uint(n / 10, count);
	*count += write(1, &"0123456789"[n % 10], 1);
}
