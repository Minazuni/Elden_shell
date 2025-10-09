/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ko-mahon <ko-mahon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/24 10:28:42 by ko-mahon          #+#    #+#             */
/*   Updated: 2025/09/24 10:27:01 by ko-mahon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "elden_shell.h"

int	setup_redirections(t_cmd *cmd)
{
	int	fd;

	if (!cmd)
		return (-1);
	// redirection d'entrée : fichier -> stdin
	if (cmd->infile)
	{
		fd = open(cmd->infile, O_RDONLY);
		if (fd < 0)
			return (perror(cmd->infile), -1);
		dup2(fd, STDIN_FILENO);
		close(fd);
	}
	// redirection de sortie : stdout -> fichier
	if (cmd->outfile)
	{
		if (cmd->append)
			fd = open(cmd->outfile, O_WRONLY | O_CREAT | O_APPEND, 0644);
		else
			fd = open(cmd->outfile, O_WRONLY | O_CREAT | O_TRUNC, 0644);
		if (fd < 0)
			return (perror(cmd->outfile), -1);
		dup2(fd, STDOUT_FILENO);
		close(fd);
	}
	// redirection d'erreur : stderr -> fichier
	if (cmd->errfile)
	{
		if (cmd->err_append)
			fd = open(cmd->errfile, O_WRONLY | O_CREAT | O_APPEND, 0644);
		else
			fd = open(cmd->errfile, O_WRONLY | O_CREAT | O_TRUNC, 0644);
		if (fd < 0)
			return (perror(cmd->errfile), -1);
		dup2(fd, STDERR_FILENO);
		close(fd);
	}
	return (0);
}
