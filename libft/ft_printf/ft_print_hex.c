/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_hex.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ko-mahon <ko-mahon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/10 18:03:01 by ko-mahon          #+#    #+#             */
/*   Updated: 2025/04/14 11:50:46 by ko-mahon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_print_hex(unsigned int n, int upper)
{
	char	*base;
	char	str[9];
	int		len;
	int		i;

	if (upper == 1)
		base = "0123456789ABCDEF";
	else
		base = "0123456789abcdef";
	i = 0;
	if (n == 0)
	{
		write(1, "0", 1);
		return (1);
	}
	while (n > 0)
	{
		str[i] = base[n % 16];
		n /= 16;
		i++;
	}
	len = i;
	while (--i >= 0)
		write(1, &str[i], 1);
	return (len);
}
