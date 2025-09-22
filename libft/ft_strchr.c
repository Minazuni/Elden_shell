/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ko-mahon <ko-mahon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/25 10:48:58 by ko-mahon          #+#    #+#             */
/*   Updated: 2025/09/16 13:28:28 by ko-mahon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>

char	*ft_strchr(const char *s, int c)
{
	if (!s)
		return (NULL);
	while (*s)
	{
		if (*s == (char)c)
			return ((char *)s);
		s++;
	}
	if (c == '\0')
		return ((char *)s);
	return (NULL);
}

// #include <stdio.h>

// int	main(void)
// {
// 	const char *str = "Bonjour tout le monde !";
// 	char ch = 't';

// 	// Test avec un caractère trouvé dans la chaîne
// 	char *result = ft_strchr(str, ch);
// 	if (result)
// 	{
// 		printf("Le caractère '%c' a été trouvé à la position : %ld\n", ch,
// 			result - str);
// 	}
// 	else
// 	{
// 		printf("Le caractère '%c' n'a pas été trouvé.\n", ch);
// 	}

// 	// Test avec un caractère non trouvé dans la chaîne
// 	ch = 'z';
// 	result = ft_strchr(str, ch);
// 	if (result)
// 	{
// 		printf("Le caractère '%c' a été trouvé à la position : %ld\n", ch,
// 			result - str);
// 	}
// 	else
// 	{
// 		printf("Le caractère '%c' n'a pas été trouvé.\n", ch);
// 	}

// 	// Test avec le caractère nul '\0'
// 	ch = '\0';
// 	result = ft_strchr(str, ch);
// 	if (result)
// 	{
// 		printf("Le caractère nul a été trouvé à la fin de la chaîne.\n");
// 	}
// 	else
// 	{
// 		printf("Le caractère nul n'a pas été trouvé.\n");
// 	}

// 	return (0);
// }