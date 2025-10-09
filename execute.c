/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ko-mahon <ko-mahon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/24 10:29:04 by ko-mahon          #+#    #+#             */
/*   Updated: 2025/09/24 14:12:21 by ko-mahon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "elden_shell.h"

int	exec_pipeline(t_cmd *cmds, t_env *env)
{
	int pipefd[2];
	t_cmd *current;
	pid_t pid;

	current = cmds;

	while (current)
	{
		if (current->next && pipe(pipefd) < 0)
		{
			perror("pipe");
			return (1);
		}
	}
}