/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ko-mahon <ko-mahon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/25 10:49:04 by ko-mahon          #+#    #+#             */
/*   Updated: 2025/04/03 17:19:02 by ko-mahon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>

int	ft_strlen(const char *s)
{
	int	i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}

size_t	ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	size_t	dest_len;
	size_t	src_len;
	size_t	i;

	dest_len = ft_strlen(dst);
	src_len = ft_strlen(src);
	if (dstsize <= dest_len)
		return (dstsize + src_len);
	i = 0;
	while (src[i] != '\0' && dest_len + i + 1 < dstsize)
	{
		dst[dest_len + i] = src[i];
		i++;
	}
	dst[dest_len + i] = '\0';
	return (dest_len + src_len);
}

// #include <stdio.h>

// int	main(void)
// {
// 	char	dest[20] = "Bonjour";
// 	char	src[] = " tout le monde!";
// 	size_t	size;
// 	size_t	result;
// 	char	dest2[10] = "Hello";
// 	size_t	small_size;

// 	size = 20;
// 	printf("Avant strlcat: dest = \"%s\"\n", dest);
// 	result = ft_strlcat(dest, src, size);
// 	printf("Après strlcat: dest = \"%s\"\n", dest);
// 	printf("Longueur totale possible de dest si taille suffisante : %zu\n",
// 		result);
// 	// Test avec un size plus petit que la taille de dest + src
// 	small_size = 10;
// 	printf("\nAvant strlcat avec petite taille: dest2 = \"%s\"\n", dest2);
// 	result = ft_strlcat(dest2, src, small_size);
// 	printf("Après strlcat avec petite taille: dest2 = \"%s\"\n", dest2);
// 	printf("Longueur totale possible de dest2 si taille suffisante : %zu\n",
// 		result);
// 	return (0);
// }
