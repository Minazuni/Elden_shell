/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kiki <kiki@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/06 10:03:36 by kiki              #+#    #+#             */
/*   Updated: 2025/10/06 10:03:38 by kiki             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "elden_shell.h"

t_env	*init_env(char **envp)
{
	t_env	*head;
	t_env	*current;
	t_env	*new;
	char	*sep;
	int		i;

	head = NULL;
	current = NULL;
	i = 0;
	while (envp[i])
	{
		sep = strchr(envp[i], '=');
		if (sep)
		{
			new = malloc(sizeof(t_env));
			new->key = ft_strndup(envp[i], sep - envp[i]);
			new->value = ft_strdup(sep + 1);
			new->next = NULL;
			if (!head)
				head = new;
			else
				current->next = new;
			current = new;
		}
		i++;
	}
	return (head);
}

void	free_tokens(t_token *tokens)
{
	t_token	*tmp;

	while (tokens)
	{
		tmp = tokens;
		tokens = tokens->next;
		free(tmp->value);
		free(tmp);
	}
}

void	free_cmds(t_cmd *cmds)
{
	t_cmd	*tmp;
	int		i;

	while (cmds)
	{
		tmp = cmds;
		cmds = cmds->next;
		if (tmp->argv)
		{
			i = 0;
			while (tmp->argv[i])
				free(tmp->argv[i++]);
			free(tmp->argv);
		}
		if (tmp->infile)
			free(tmp->infile);
		if (tmp->outfile)
			free(tmp->outfile);
		if (tmp->errfile)
			free(tmp->errfile);
		free(tmp);
	}
}

void	free_env(t_env *env)
{
	t_env	*tmp;

	while (env)
	{
		tmp = env;
		env = env->next;
		free(tmp->key);
		free(tmp->value);
		free(tmp);
	}
}