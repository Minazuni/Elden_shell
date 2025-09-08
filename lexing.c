/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexing.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: refeunte <refeunte@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/25 14:59:26 by refeunte          #+#    #+#             */
/*   Updated: 2025/09/08 13:28:08 by refeunte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stddef.h>

char *ft_strndup(const char *s, size_t n) 
{
    char *dup = malloc(n + 1);
    char *godrick;
    if (!dup)
        return NULL;
    godrick = dup;
    while (n-- && *s)
        *godrick++ = *s++;
    *godrick = '\0';
    return dup;
}

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
    const char *radhan = line;

    while (*radhan)
    {//on igniore les espaces trql t'as capté
        if (ft_isspace(*radhan))
        {
            radhan++;
            continue;
        }
        if (*radhan == '|' || *radhan == '<' || *radhan == '>')//voir s'il faut gérer les >>
        {//gérer les cas spéciaux, les opérateurs et touts
            t_token *token = ft_new_token(radhan, 1);
            if (!head)
                head = token;
            else
                tail->next = token;
            tail = token;
            radhan++;
            continue;
        }
        
        const char *start = radhan;
        while (*radhan && !ft_isspace(*radhan) && *radhan != '|' && *radhan != '>' && *radhan != '<')
            radhan++;
        t_token *token = ft_new_token(start, radhan - start);
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
    const char *line = "cat file.txt | grep hello > < out.txt";
    t_token *token = ft_lexer(line);
    ft_print_token(token);
    return (0);//free malenia
}