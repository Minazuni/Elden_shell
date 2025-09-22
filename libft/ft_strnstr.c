/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ko-mahon <ko-mahon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/25 10:49:15 by ko-mahon          #+#    #+#             */
/*   Updated: 2025/04/03 17:02:33 by ko-mahon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	size_t	j;
	size_t	i;

	j = 0;
	i = 0;
	if (*needle == '\0')
	{
		return ((char *)haystack);
	}
	while (i < len && haystack[i])
	{
		if (haystack[i] == needle[0])
		{
			while ((needle[j]) && (haystack[i + j] == needle[j]) && (i
					+ j < len))
			{
				j++;
			}
			if (needle[j] == '\0')
				return ((char *)(haystack + i));
		}
		i++;
	}
	return (NULL);
}
