/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ko-mahon <ko-mahon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/02 14:09:14 by ko-mahon          #+#    #+#             */
/*   Updated: 2025/04/04 11:31:06 by ko-mahon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(const char *s1, const char *s2)
{
	size_t	lens1;
	size_t	lens2;
	char	*result;

	if (!s1 && !s2)
	{
		result = malloc(1);
		if (!result)
			return (NULL);
		result[0] = '\0';
		return (result);
	}
	lens1 = ft_strlen(s1);
	lens2 = ft_strlen(s2);
	result = malloc(sizeof(char) * (lens1 + lens2 + 1));
	if (!result)
		return (NULL);
	ft_memcpy(result, s1, lens1);
	ft_memcpy(result + lens1, s2, lens2);
	result[lens1 + lens2] = '\0';
	return (result);
}

// int	main(void)
// {
// 	char *s1[] = {"Hello"};
// 	char *s2[] = {"world"};
// 	char *result;

// 	result = ft_strjoin(*s1, *s2);
// 	if (result)
// 	{
// 		printf("Test 1: %s\n", result);
// 		free(result);
// 	}
// 	return (0);
// }