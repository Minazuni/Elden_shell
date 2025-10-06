/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ko-mahon <ko-mahon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/22 10:51:18 by ko-mahon          #+#    #+#             */
/*   Updated: 2025/09/22 13:06:47 by ko-mahon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "elden_shell.h"

void	add_cmd_to_list(t_cmd **head, t_cmd *new_cmd)
{
	t_cmd	*tmp;

	if (!head || !new_cmd)
		return ;
	if (!*head) // la liste est vide = new_cmd devient head
	{
		*head = new_cmd;
		return ;
	}
	tmp = *head;
	while (tmp->next) // on avance jusqu’au dernier
		tmp = tmp->next;
	tmp->next = new_cmd;
}

t_cmd	*init_cmd(void)
{
	t_cmd	*new;

	new = malloc(sizeof(t_cmd));
	if (!new)
		return (NULL);
	new->argv = NULL;
	new->infile = NULL;
	new->outfile = NULL;
	new->append = 0;
	new->next = NULL;
	return (new);
}
int	is_word(char *str)
{
	if (!str)
		return (0);
	if (strcmp(str, "|") == 0)
		return (0);
	if (strcmp(str, "<") == 0)
		return (0);
	if (strcmp(str, ">") == 0)
		return (0);
	if (strcmp(str, ">>") == 0)
		return (0);
	return (1); // sinon c'est un mot normal
}

void	add_to_argv(t_cmd *cmd, char *word)
{
	char	**new_argv;
	int		i;

	if (!cmd || !word)
		return ;
	// compte le nombre d'éléments existants
	i = 0;
	if (cmd->argv)
	{
		while (cmd->argv[i])
			i++;
	}
	// allouer un nouveau tableau avec un slot supplémentaire
	new_argv = (char **)malloc(sizeof(char *) * (i + 2));
	if (!new_argv)
		return ;
	// copie l'ancien argv
	i = 0;
	while (cmd->argv && cmd->argv[i])
	{
		new_argv[i] = cmd->argv[i];
		i++;
	}
	// ajouter le nouveau mot
	new_argv[i] = ft_strdup(word);
	new_argv[i + 1] = NULL;
	// libérer l'ancien argv si besoin
	if (cmd->argv)
		free(cmd->argv);
	cmd->argv = new_argv;
}
