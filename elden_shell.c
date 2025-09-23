/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   elden_shell.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ko-mahon <ko-mahon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/03 17:40:28 by ko-mahon          #+#    #+#             */
/*   Updated: 2025/09/23 11:54:18 by ko-mahon         ###   ########.fr       */
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

int main(int argc, char **argv)
{
    char *line;
    t_token *tokens;
    t_cmd *cmds;

    if (argc < 2)
    {
        printf("Usage: %s <command>\n", argv[0]);
        return (1);
    }

    // assembler tous les argv[1..argc-1] en une seule ligne
    size_t len = 0;
    for (int i = 1; i < argc; i++)
        len += strlen(argv[i]) + 1; // +1 pour l'espace
    line = malloc(len);
    if (!line)
        return (1);

    line[0] = '\0';
    for (int i = 1; i < argc; i++)
    {
        strcat(line, argv[i]);
        if (i != argc - 1)
            strcat(line, " ");
    }

    printf("Input: %s\n\n", line);

    // 1. Lexing
    tokens = ft_lexer(line);
    ft_print_token(tokens);

    // 2. Parsing
    cmds = parse_tokens(tokens);
    print_cmds(cmds);

    free(line);
    return (0);
}

