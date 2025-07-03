/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wheino <wheino@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/03 15:31:15 by wheino            #+#    #+#             */
/*   Updated: 2025/06/09 14:55:07 by wheino           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_printf(const char *str, ...)
{
	va_list	ap;
	int		chars_written;

	if (!str)
		return (-1);
	va_start(ap, str);
	chars_written = loop_str(str, &ap);
	va_end(ap);
	return (chars_written);
}

int	loop_str(const char *str, va_list *ap)
{
	int	chars_written;
	int	res;

	chars_written = 0;
	res = 0;
	while (*str != '\0')
	{
		if (*str == '%')
		{
			str++;
			if (*str != '\0')
				res = handle_format(*str++, ap);
			if (res < 0)
				return (-1);
			chars_written += res;
		}
		else
		{
			if (write(1, str, 1) < 0)
				return (-1);
			chars_written++;
			str++;
		}
	}
	return (chars_written);
}

int	handle_format(char specifier, va_list *ap)
{
	int		chars_written;

	chars_written = 0;
	if (specifier == 'c')
		chars_written = print_char(va_arg(*ap, int));
	else if (specifier == 's')
		chars_written = print_str(va_arg(*ap, char *));
	else if (specifier == 'd' || specifier == 'i')
		chars_written = print_signed(va_arg(*ap, int));
	else if (specifier == 'u')
		chars_written = print_unsigned(va_arg(*ap, int));
	else if (specifier == 'x')
		chars_written = print_hex_low(va_arg(*ap, unsigned int));
	else if (specifier == 'X')
		chars_written = print_hex_up(va_arg(*ap, unsigned int));
	else if (specifier == 'p')
		chars_written = print_pointer(va_arg(*ap, void *));
	else if (specifier == '%')
		chars_written = print_char(specifier);
	return (chars_written);
}

int	print_hex_low(unsigned long long n)
{
	char	*hex_digits;
	char	buffer[16];
	int		chars_written;
	int		i;

	hex_digits = "0123456789abcdef";
	chars_written = 0;
	if (n == 0)
		return (print_char('0'));
	i = 0;
	while (n > 0)
	{
		buffer[i++] = hex_digits[n % 16];
		n = n / 16;
	}
	while (--i >= 0)
	{
		if (write(1, &buffer[i], 1) != 1)
			return (-1);
		else
			chars_written++;
	}
	return (chars_written);
}

int	print_hex_up(unsigned long long n)
{
	char	*hex_digits;
	char	buffer[16];
	int		chars_written;
	int		i;

	hex_digits = "0123456789ABCDEF";
	chars_written = 0;
	if (n == 0)
		return (print_char('0'));
	i = 0;
	while (n > 0)
	{
		buffer[i++] = hex_digits[n % 16];
		n = n / 16;
	}
	while (--i >= 0)
	{
		if (write(1, &buffer[i], 1) != 1)
			return (-1);
		else
			chars_written++;
	}
	return (chars_written);
}
