/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   elden_shell.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+
	+:+     */
/*   By: ko-mahon <ko-mahon@student.42.fr>          +#+  +:+
	+#+        */
/*                                                +#+#+#+#+#+
	+#+           */
/*   Created: 2025/09/03 17:40:28 by ko-mahon          #+#    #+#             */
/*   Updated: 2025/09/23 11:54:18 by ko-mahon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "elden_shell.h"


void	print_cmds(t_cmd *cmds)
{
	int i;

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
		if (cmds->errfile)
			printf("errfile = %s (%s)\n", cmds->errfile,
				cmds->err_append ? "append" : "truncate");
		cmds = cmds->next;
	}
}

int main(int argc, char **argv, char **envp)
{
    (void)argc;  // pour éviter le warning
    (void)argv;  // idem
    t_env *env;
    char *line = NULL;
    size_t len = 0;
    t_token *tokens;
    t_cmd *cmds;

    env = init_env(envp);

    while (1)
    {
        printf("Elden$ ");
        fflush(stdout);
        
        if (getline(&line, &len, stdin) == -1)
        {
            printf("\n");
            break;
        }

        if (line[0] == '\n')
            continue;

        line[strcspn(line, "\n")] = '\0';

        tokens = ft_lexer(line);
        cmds = parse_tokens(tokens);

        exec_pipeline(cmds, env);  // ret n’est plus stocké

        free_tokens(tokens);
        free_cmds(cmds);
    }

    free(line);
    free_env(env);
    return 0;
}

