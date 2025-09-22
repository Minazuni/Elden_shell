/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_pointer.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ko-mahon <ko-mahon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 10:04:18 by ko-mahon          #+#    #+#             */
/*   Updated: 2025/04/14 11:46:14 by ko-mahon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	ft_put_ptr(uintptr_t ptr)
{
	int		count;
	char	*base;

	count = 0;
	base = "0123456789abcdef";
	if (ptr >= 16)
		count += ft_put_ptr(ptr / 16);
	count += write(1, &base[ptr % 16], 1);
	return (count);
}

int	ft_print_pointer(void *ptr)
{
	int	count;

	count = 0;
	if (!ptr)
		return (write(1, "(nil)", 5));
	count += write(1, "0x", 2);
	count += ft_put_ptr((uintptr_t)ptr);
	return (count);
}
