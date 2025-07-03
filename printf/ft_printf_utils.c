/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wheino <wheino@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/03 15:31:04 by wheino            #+#    #+#             */
/*   Updated: 2025/06/09 14:52:11 by wheino           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	print_char(int c)
{
	char	ch;

	ch = (char)c;
	if (write(1, &ch, 1) < 1)
		return (-1);
	else
		return (1);
}

int	print_str(char *s)
{
	int	i;

	if (s == NULL)
	{
		if (write(1, "(null)", 6) < 0)
			return (-1);
		else
			return (6);
	}
	i = 0;
	while (s[i] != '\0')
	{
		if (write(1, &s[i], 1) < 0)
			return (-1);
		i++;
	}
	return (i);
}

int	print_signed(int n)
{
	int	chars_written;
	int	res;

	chars_written = 0;
	if (n == -2147483648)
	{
		chars_written = write(1, "-2147483648", 11);
		if (chars_written < 1)
			return (-1);
		else
			return (chars_written);
	}
	if (n < 0)
	{
		chars_written += write(1, "-", 1);
		if (chars_written < 1)
			return (-1);
		n = -n;
	}
	res = print_unsigned(n);
	if (res < 0)
		return (-1);
	chars_written += res;
	return (chars_written);
}

int	print_unsigned(unsigned int n)
{
	char	digit;
	int		chars_written;

	chars_written = 0;
	if (n > 9)
		chars_written = print_unsigned(n / 10);
	digit = n % 10 + '0';
	if (write(1, &digit, 1) < 1)
		return (-1);
	return (chars_written + 1);
}

int	print_pointer(void *p)
{
	int	chars_written;
	int	res;

	if (!p)
	{
		chars_written = print_str("(nil)");
		if (chars_written < 5)
			return (-1);
		return (chars_written);
	}
	chars_written = print_str("0x");
	if (chars_written < 2)
		return (-1);
	res = print_hex_low((unsigned long long)p);
	if (res < 0)
		return (-1);
	chars_written += res;
	return (chars_written);
}
