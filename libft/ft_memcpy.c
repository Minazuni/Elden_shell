/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ko-mahon <ko-mahon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/25 10:48:49 by ko-mahon          #+#    #+#             */
/*   Updated: 2025/04/02 10:55:02 by ko-mahon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	unsigned char		*d;
	const unsigned char	*s;
	size_t				i;

	i = 0;
	d = (unsigned char *)dst;
	s = (const unsigned char *)src;
	if (!dst && !src && n > 0)
	{
		return (NULL);
	}
	while (n--)
	{
		*d++ = *s++;
		i++;
	}
	return (dst);
}
