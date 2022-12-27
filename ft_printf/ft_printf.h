/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmethawa <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/27 19:22:02 by kmethawa          #+#    #+#             */
/*   Updated: 2022/12/27 19:23:32 by kmethawa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <stdio.h>
# include <stdarg.h>
# include <unistd.h>
# include <stdlib.h>
# include <stdint.h>

int		ft_printf(const char *format, ...);
int		print_string(char *str);
int		print_char(char c);
void	print_int(int64_t n, int *count);
void	print_uint(uint64_t n, int *count);
void	print_hex(uint64_t n, int *count, char *charset);
void	print_pointer(uintptr_t n, int *count);
int		format_check(const char *format, va_list args, int *count, int i);

#endif
