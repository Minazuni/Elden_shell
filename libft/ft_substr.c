/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ko-mahon <ko-mahon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/02 14:09:01 by ko-mahon          #+#    #+#             */
/*   Updated: 2025/04/04 16:14:03 by ko-mahon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>

static char	*empty_string(void)
{
	char	*dest;

	dest = (char *)malloc(1);
	if (!dest)
		return (NULL);
	dest[0] = '\0';
	return (dest);
}

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	size_t	srclen;
	size_t	dstlen;
	char	*dest;
	size_t	i;

	if (!s)
		return (NULL);
	srclen = ft_strlen(s);
	if (start >= srclen)
		return (empty_string());
	dstlen = srclen - start;
	if (dstlen > len)
		dstlen = len;
	dest = malloc(dstlen + 1);
	if (!dest)
		return (NULL);
	i = 0;
	while (i < dstlen)
	{
		dest[i] = s[start + i];
		i++;
	}
	dest[i] = '\0';
	return (dest);
}

// int	main(void)
// {
// 		char s[] = "substr function Implementation";

// 		int start = 7;
// 		size_t len = 12;

// 	char *dest = ft_substr(TESTED_STRING , 40, 25);

// 	printf("%s\n", dest);
// 	free(dest);

// 	return (0);
// }