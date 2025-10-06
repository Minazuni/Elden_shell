/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+        
	+:+     */
/*   By: ko-mahon <ko-mahon@student.42.fr>          +#+  +:+      
	+#+        */
/*                                                +#+#+#+#+#+  
	+#+           */
/*   Created: 2025/09/03 17:40:00 by ko-mahon          #+#    #+#             */
/*   Updated: 2025/09/23 12:08:20 by ko-mahon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "elden_shell.h"


t_cmd	*parse_tokens(t_token *tokens)
{
	t_cmd *head;
	t_cmd *current_cmd;

	head = NULL;
	current_cmd = NULL;

	while (tokens)
	{
		if (!current_cmd)
		{
			current_cmd = init_cmd();
			add_cmd_to_list(&head, current_cmd);
		}

		if (is_word(tokens->value))
		{
			add_to_argv(current_cmd, tokens->value);
		}
		else if (ft_strcmp(tokens->value, "2>>") == 0)
		{
			current_cmd->err_append = 1;
			if (tokens->next)
				current_cmd->errfile = ft_strdup(tokens->next->value);
			tokens = tokens->next;
		}
		else if (ft_strcmp(tokens->value, "2>") == 0)
		{
			current_cmd->err_append = 0;
			if (tokens->next)
				current_cmd->errfile = ft_strdup(tokens->next->value);
			tokens = tokens->next;
		}
		else if (strcmp(tokens->value, "<") == 0)
		{
			tokens = tokens->next;
			if (tokens)
				current_cmd->infile = ft_strdup(tokens->value);
		}
		else if (strcmp(tokens->value, ">") == 0)
		{
			tokens = tokens->next;
			if (tokens)
			{
				current_cmd->outfile = ft_strdup(tokens->value);
				current_cmd->append = 0;
			}
		}
		else if (strcmp(tokens->value, ">>") == 0)
		{
			tokens = tokens->next;
			if (tokens)
			{
				current_cmd->outfile = ft_strdup(tokens->value);
				current_cmd->append = 1;
			}
		}
		else if (strcmp(tokens->value, "|") == 0)
		{
			current_cmd = NULL;
		}

		if (tokens)
			tokens = tokens->next;
	}
	return (head);
}