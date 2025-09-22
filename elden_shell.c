/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   elden_shell.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ko-mahon <ko-mahon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/03 17:40:28 by ko-mahon          #+#    #+#             */
/*   Updated: 2025/09/22 13:14:50 by ko-mahon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "elden_shell.h"
#include <stdio.h>

void	print_cmds(t_cmd *cmds)
{
	int	i;

	while (cmds)
	{
		printf("=== Command ===\n");
		i = 0;
		while (cmds->argv && cmds->argv[i])
		{
			printf("argv[%d] = %s\n", i, cmds->argv[i]);
			i++;
		}
		if (cmds->infile)
			printf("infile  = %s\n", cmds->infile);
		if (cmds->outfile)
			printf("outfile = %s (%s)\n", cmds->outfile,
				cmds->append ? "append" : "truncate");
		cmds = cmds->next;
	}
}

int	main(void)
{
	const char	*line = "cat in.txt | grep hello >> out.txt";
	t_token		*tokens;
	t_cmd		*cmds;

	printf("Input: %s\n\n", line);
	// 1. Lexing
	tokens = ft_lexer(line);
	ft_print_token(tokens);
	// 2. Parsing
	cmds = parse_tokens(tokens);
	print_cmds(cmds);
	return (0);
}
