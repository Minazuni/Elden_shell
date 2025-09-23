/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ko-mahon <ko-mahon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/23 14:30:51 by ko-mahon          #+#    #+#             */
/*   Updated: 2025/09/23 14:55:43 by ko-mahon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "elden_shell.h"

int	setup_redirections(t_cmd *cmd)
{
	int fd;

	if (!cmd)
		return (-1);
	if (cmd->infile)
	{
		fd = open(cmd->infile, O_RDONLY);
		if (fd < 0)
		{
			perror(cmd->infile);
			return (-1);
		}
		dup2(fd, STDIN_FILENO);
		close(fd);
	}
	if (cmd->outfile)
	{
		if (cmd->append)
			fd = open(cmd->outfile, O_APPEND);
		// si append on ajoute a la fin du fichier
		else
			fd = open(cmd->outfile, O_TRUNC); // sinon un ecrase
		if (fd < 0)
		{
			perror(cmd->outfile);
			return (-1);
		}

		dup2(fd, STDOUT_FILENO);
		close(fd);
	}
	if (cmd->errfile)
	{
		if (cmd->err_append)
			fd = open(cmd->err_append, O_RDONLY | O_WRONLY | O_APPEND, 0644);
		else
			fd = open(cmd->err_append, O_RDONLY | O_WRONLY | O_TRUNC, 0644);

		if (fd < 0)
		{
			perror(cmd->errfile);
			return (-1);
		}
		dup2(fd, STDERR_FILENO);
		close(fd);
	}
}