/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcat                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kiki <kiki@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/07 10:55:23 by kiki              #+#    #+#             */
/*   Updated: 2025/10/07 10:55:39 by kiki             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char *ft_strcat(char *dest, const char *src)
{
    int i;
    int j;

    if (!dest || !src)
        return (dest);

    i = 0;
    while (dest[i] != '\0')
        i++;

    j = 0;
    while (src[j] != '\0')
    {
        dest[i + j] = src[j];
        j++;
    }

    dest[i + j] = '\0';
    return (dest);
}
