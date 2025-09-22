/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ko-mahon <ko-mahon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/10 17:15:31 by ko-mahon          #+#    #+#             */
/*   Updated: 2025/04/14 11:55:44 by ko-mahon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <stdarg.h>
# include <stdint.h>
# include <stdlib.h>
# include <unistd.h>

int		ft_printf(const char *format, ...);

int		ft_parse(char c, va_list args);
int		ft_print_int(int n);
int		ft_print_str(char *str);
int		ft_print_char(char c);
int		ft_print_unsigned(unsigned int n);
int		ft_print_hex(unsigned int n, int upper);
int		ft_print_pointer(void *ptr);

int		ft_putchar(char c);
int		ft_putstr(char *str);
int		ft_hex_len(unsigned int n);
char	*ft_itoa(int n);

#endif
