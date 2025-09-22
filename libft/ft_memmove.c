/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ko-mahon <ko-mahon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/25 10:48:52 by ko-mahon          #+#    #+#             */
/*   Updated: 2025/04/02 10:36:16 by ko-mahon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	unsigned char		*d;
	const unsigned char	*s;

	if (!dest && !src)
		return (NULL);
	d = (unsigned char *)dest;
	s = (const unsigned char *)src;
	if (d > s && d < s + n)
		while (n--)
			d[n] = s[n];
	else
		while (n--)
			*d++ = *s++;
	return (dest);
}

// #include <stdio.h>
// #include <string.h>

// int main()
// {
//     char str1[] = "123456";
//     ft_memmove(str1 + 2, str1, 3); // Déplace "123" vers "3e place"
//     printf("%s\n", str1);  // Attendu : "121236"

//     char str2[] = "abcdef";
//     ft_memmove(str2, str2 + 2, 4); // Décale "cdef" au début
//     printf("%s\n", str2); // Attendu : "cdefef"

//     return (0);
// }