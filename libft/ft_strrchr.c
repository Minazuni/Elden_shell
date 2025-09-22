/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ko-mahon <ko-mahon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/25 10:49:20 by ko-mahon          #+#    #+#             */
/*   Updated: 2025/04/02 10:38:20 by ko-mahon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>

char	*ft_strrchr(const char *s, int c)
{
	char	*last;

	last = (NULL);
	while (*s)
	{
		if (*s == (char)c)
		{
			last = (char *)s;
		}
		s++;
	}
	if (c == '\0')
	{
		return ((char *)s);
	}
	return (last);
}

// #include <stdio.h>
// #include <string.h>

// int main()
// {
//     const char str[] = "Hello, world!";
//     char ch = 'o';

//     printf("ft_strrchr  : %s\n", ft_strrchr(str, ch));
//     printf("strrchr     : %s\n", strrchr(str, ch));
// Pour comparer avec la vraie fonction

//     return (0);
// }
