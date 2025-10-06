#ifndef ELDEN_SHELL_H
# define ELDEN_SHELL_H

# include "libft/libft.h"
# include <fcntl.h>
# include <signal.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/wait.h>
# include <unistd.h>

/* ------------------- TOKEN ------------------- */
typedef struct s_token
{
	char			*value;
	struct s_token	*next;
}					t_token;

/* ------------------- COMMAND ------------------- */
typedef struct s_cmd
{
	char **argv;   // arguments de la commande
	char *infile;  // fichier d'entrée
	char *outfile; // fichier de sortie (stdout)
	int append;    // mode append pour stdout

	char *errfile;  // fichier de sortie (stderr)
	int err_append; // mode append pour stderr

	struct s_cmd *next; // commande suivante (si pipe)
}					t_cmd;

/* ------------------- ENVIRONNEMENT ------------------- */
typedef struct s_env
{
	char *key;          // le nom de la variable (ex: "PATH")
	char *value;        // sa valeur (ex: "/usr/bin:/bin")
	struct s_env *next; // pointeur vers la variable suivante
}					t_env;

/* ------------------- lexing.c ------------------- */
char				*ft_strndup(const char *s, size_t n);
int					ft_isspace(char c);
t_token				*ft_new_token(const char *start, int len);
t_token				*ft_lexer(const char *line);
void				ft_print_token(t_token *token);

/* ---------------------parsing_utils.c-------------------------*/
void				add_cmd_to_list(t_cmd **head, t_cmd *new_cmd);
t_cmd				*init_cmd(void);
int					is_word(char *str);
void				add_to_argv(t_cmd *cmd, char *word);

/* -----------------------parsing.c -----------------------*/
t_cmd				*parse_tokens(t_token *tokens);
/* ------------------- EXECUTION ------------------- */
int					exec_cmd(t_cmd *cmd, t_env *env);
int					exec_pipeline(t_cmd *cmds, t_env *env);
int					exec_builtin(t_cmd *cmd, t_env *env);

/* ------------------- REDIRECTIONS ------------------- */
int					setup_redirections(t_cmd *cmd);

#endif
