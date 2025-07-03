/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wheino <wheino@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/03 15:30:38 by wheino            #+#    #+#             */
/*   Updated: 2025/06/09 13:45:30 by wheino           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <stdarg.h>
# include <unistd.h>

int	ft_printf(const char *format, ...);
int	handle_format(char specifier, va_list *ap);
int	loop_str(const char *str, va_list *ap);
int	print_char(int c);
int	print_str(char *s);
int	print_signed(int n);
int	print_unsigned(unsigned int n);
int	print_hex_low(unsigned long long n);
int	print_hex_up(unsigned long long n);
int	print_pointer(void *p);
#endif
