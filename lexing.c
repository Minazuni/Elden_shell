/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexing.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ko-mahon <ko-mahon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/25 14:59:26 by refeunte          #+#    #+#             */
/*   Updated: 2025/09/22 14:18:40 by ko-mahon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ctype.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char	*ft_strndup(const char *s, size_t n)
{
	char	*dup;
	char	*godrick;

	dup = malloc(n + 1);
	if (!dup)
		return (NULL);
	godrick = dup;
	while (n-- && *s)
		*godrick++ = *s++;
	*godrick = '\0';
	return (dup);
}

int	ft_isspace(char c)
{
	return (c == ' ' || c == '\t');
}

typedef struct s_token
{
	char			*value;
	struct s_token	*next;
}					t_token;

t_token	*ft_new_token(const char *start, int len)
{
	t_token	*token;

	token = malloc(sizeof(t_token));
	token->value = ft_strndup(start, len);
	//  strndup pour créer une copie independante,
	// chacun de mes petits token ont leurs propres chaines,
	// 	ca dépends plus de la ligne d'entrée token->next = NULL;
	return (token);
	// free malenia
}

t_token	*ft_lexer(const char *line)
{
	t_token		*head = NULL;
	t_token		*tail = NULL;
	t_token		*token;
	const char	*start;

	while (*line)
	{
		// Ignorer les espaces
		if (ft_isspace(*line))
		{
			line++;
			continue;
		}

		// Gérer les opérateurs spéciaux
		if (*line == '|')
		{
			token = ft_new_token(line, 1);
			line++;
		}
		else if (*line == '<')
		{
			token = ft_new_token(line, 1);
			line++;
		}
		else if (*line == '>' && *(line + 1) == '>')
		{
			token = ft_new_token(line, 2);
			line += 2;
		}
		else if (*line == '>')
		{
			token = ft_new_token(line, 1);
			line++;
		}
		else
		{
			// C’est un mot
			start = line;
			while (*line && !ft_isspace(*line) && *line != '|' 
				&& *line != '<' && *line != '>')
				line++;
			token = ft_new_token(start, line - start);
		}

		// Ajouter le token à la liste
		if (!head)
			head = token;
		else
			tail->next = token;
		tail = token;
	}
	return (head);
}

void	ft_print_token(t_token *token)
{
	while (token)
	{
		printf("TOKEN: [%s]\n", token->value);
		token = token->next;
	}
}
