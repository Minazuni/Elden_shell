/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ko-mahon <ko-mahon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/03 17:40:00 by ko-mahon          #+#    #+#             */
/*   Updated: 2025/09/22 12:54:43 by ko-mahon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "elden_shell.h"

t_cmd	*parse_tokens(t_token *tokens)
{
	t_cmd	*head;
	t_cmd	*current_cmd;

	head = NULL;
	current_cmd = NULL;
	while (tokens)
	{
		// 1. Si on commence une nouvelle commande
		if (!current_cmd)
		{
			current_cmd = init_cmd();
			add_cmd_to_list(&head, current_cmd);
		}
		// 2. Vérifier le type du token
		if (is_word(tokens->value))
		{
			add_to_argv(current_cmd, tokens->value);
		}
		else if (strcmp(tokens->value, "<") == 0)
		{
			tokens = tokens->next; // avancer au fichier
			current_cmd->infile = ft_strdup(tokens->value);
		}
		else if (strcmp(tokens->value, ">") == 0)
		{
			tokens = tokens->next;
			current_cmd->outfile = strdup(tokens->value);
			current_cmd->append = 0;
		}
		else if (strcmp(tokens->value, ">>") == 0)
		{
			tokens = tokens->next;
			current_cmd->outfile = strdup(tokens->value);
			current_cmd->append = 1;
		}
		else if (strcmp(tokens->value, "|") == 0)
		{
			// fin de la commande courante
			current_cmd = NULL;
		}
		tokens = tokens->next;
	}
	return (head);
}
