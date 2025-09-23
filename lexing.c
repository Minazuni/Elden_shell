/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexing.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ko-mahon <ko-mahon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/25 14:59:26 by refeunte          #+#    #+#             */
/*   Updated: 2025/09/23 11:57:22 by ko-mahon         ###   ########.fr       */
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
	t_token		*head;
	t_token		*tail;
	const char	*radhan = line;
	t_token		*token;
	const char	*start;
	char		quote;

	head = NULL;
	tail = NULL;
	while (*radhan)
	{
		if (ft_isspace(*radhan))
		{
			radhan++;
			continue ;
		}
		// Pipes
		if (*radhan == '|')
		{
			token = ft_new_token(radhan, 1);
			radhan++;
		}
		// Redirections stderr
		else if (*radhan == '2' && *(radhan + 1) == '>' && *(radhan + 2) == '>')
		{
			token = ft_new_token(radhan, 3); // 2>>
			radhan += 3;
		}
		else if (*radhan == '2' && *(radhan + 1) == '>')
		{
			token = ft_new_token(radhan, 2); // 2>
			radhan += 2;
		}
		// Redirections stdin
		else if (*radhan == '<')
		{
			token = ft_new_token(radhan, 1);
			radhan++;
		}
		// Redirections stdout
		else if (*radhan == '>' && *(radhan + 1) == '>')
		{
			token = ft_new_token(radhan, 2); // >>
			radhan += 2;
		}
		else if (*radhan == '>')
		{
			token = ft_new_token(radhan, 1);
			radhan++;
		}
		// Quotes simples ou doubles
		else if (*radhan == '\'' || *radhan == '"')
		{
			quote = *radhan;
			radhan++;       // skip ouverture quote
			start = radhan; // début du contenu
			while (*radhan && *radhan != quote)
				radhan++;
			token = ft_new_token(start, radhan - start);
			if (*radhan == quote)
				radhan++; // skip fermeture quote
		}
		// Mot normal
		else
		{
			start = radhan;
			while (*radhan && !ft_isspace(*radhan) && *radhan != '|'
				&& *radhan != '<' && *radhan != '>')
				radhan++;
			token = ft_new_token(start, radhan - start);
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
