/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parse.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ko-mahon <ko-mahon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/10 18:31:54 by ko-mahon          #+#    #+#             */
/*   Updated: 2025/04/16 15:58:24 by ko-mahon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_putchar(char c)
{
	write(1, &c, 1);
	return (1);
}

int	ft_putstr(char *str)
{
	int	len;

	if (!str)
		str = "(null)";
	len = 0;
	while (str[len])
	{
		write(1, &str[len], 1);
		len++;
	}
	return (len);
}

int	ft_putnbr(int n)
{
	int		len;
	char	num[11];
	int		i;

	if (n == 0)
		return (write(1, "0", 1));
	if (n == -2147483648)
		return (write(1, "-2147483648", 11));
	len = 0;
	if (n < 0)
	{
		write(1, "-", 1);
		n = -n;
		len = 1;
	}
	i = 0;
	while (n > 0)
	{
		num[i++] = n % 10 + '0';
		n /= 10;
	}
	while (--i >= 0)
		len += write(1, &num[i], 1);
	return (len);
}

int	ft_puthex(unsigned int n, const char format)
{
	char	*hex_base;
	char	num[8];
	int		i;
	int		len;

	if (format == 'x')
		hex_base = "0123456789abcdef";
	else
		hex_base = "0123456789ABCDEF";
	if (n == 0)
		return (write(1, "0", 1));
	i = 0;
	len = 0;
	while (n > 0)
	{
		num[i++] = hex_base[n % 16];
		n /= 16;
	}
	while (--i >= 0)
		len += write(1, &num[i], 1);
	return (len);
}

int	ft_parse(char c, va_list args)
{
	if (c == 'd' || c == 'i')
		return (ft_print_int(va_arg(args, int)));
	else if (c == 's')
		return (ft_print_str(va_arg(args, char *)));
	else if (c == 'c')
		return (ft_print_char(va_arg(args, int)));
	else if (c == 'u')
		return (ft_print_unsigned(va_arg(args, unsigned int)));
	else if (c == 'x')
		return (ft_print_hex(va_arg(args, unsigned int), 0));
	else if (c == 'X')
		return (ft_print_hex(va_arg(args, unsigned int), 1));
	else if (c == 'p')
		return (ft_print_pointer(va_arg(args, void *)));
	else if (c == '%')
		return (write(1, "%", 1));
	return (0);
}
