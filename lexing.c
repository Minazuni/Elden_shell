/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexing.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: refeunte <refeunte@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/25 14:59:26 by refeunte          #+#    #+#             */
/*   Updated: 2025/09/04 16:34:49 by refeunte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

int ft_isspace(char c) 
{
    return (c == ' ' || c == '\t');
}

typedef struct s_token 
{
    char *value;
    struct s_token *next;
} t_token;

t_token *ft_new_token(const char *start, int len)
{
    t_token *token = malloc(sizeof(t_token));
    token->value = ft_strndup(start, len);//strndup pour créer une copie independante, chacun de mes petits token ont leurs propres chaines, ca dépends plus de la ligne d'entrée
    token->next = NULL;
    return token; //free malenia
}

t_token *ft_lexer(const char *line)
{
    t_token *head = NULL;
    t_token *tail = NULL;
    const char *radan = line;

    while (*radan)
    {//on igniore les espaces trql t'as capté
        if (ft_isspace(*radan))
        {
            radan++;
            continue;
        }
        if (*radan == '|' || *radan == '<' || *radan == '>' || *radan == '>>')
        {//gérer les cas spéciaux, les opérateurs et touts
            t_token *token = ft_new_token(radan, 1);
            if (!head)
                head = token;
            else
                tail->next = token;
                radan++;
                continue;
        }
        
        const char *start = radan;
        while (*radan && ft_isspace(*radan) && *radan != '|' && *radan != '>' && *radan != '<' && *radan != '>>')
            radan++;
        t_token *token = ft_new_token(start, p - start);
        if (!head)
            head = token;
        else
            tail->next = token;
        tail = token;
    }
    return head;
}
    
void ft_print_token(t_token *token)
{
    while (token)
    {
        printf("TOKEN: [%s]\n", token->value);
        token = token->next;
    }
}

int main()
{
    const char *line = "cat file.txt | grep hello > out.txt";
    t_token *token = ft_lexer(line);
    ft_print_token(token);
    return (0);//free malenia
}