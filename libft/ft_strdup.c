/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ko-mahon <ko-mahon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/01 17:38:49 by ko-mahon          #+#    #+#             */
/*   Updated: 2025/04/03 16:40:54 by ko-mahon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s)
{
	int		len;
	int		i;
	char	*duplicat;

	if (!s)
		return (NULL);
	len = ft_strlen(s) + 1;
	duplicat = malloc(len);
	if (!duplicat)
		return (NULL);
	i = 0;
	while (i < len - 1)
	{
		duplicat[i] = s[i];
		i++;
	}
	duplicat[i] = '\0';
	return (duplicat);
}
