/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+
	+:+     */
/*   By: ko-mahon <ko-mahon@student.42.fr>          +#+  +:+
	+#+        */
/*                                                +#+#+#+#+#+
	+#+           */
/*   Created: 2025/09/29 11:00:17 by marvin            #+#    #+#             */
/*   Updated: 2025/10/06 00:00:00 by ko-mahon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "elden_shell.h"


int	count_env(t_env *env)
{
	int count;
	t_env *tmp;

	count = 0;
	tmp = env;
	while (tmp != NULL)
	{
		count++;
		tmp = tmp->next;
	}
	return (count);
}

char	*kv_join(char *key, char *value)
{
	char *line;
	int len_key;
	int len_val;
	int total_len;

	len_key = 0;
	len_val = 0;
	if (key != NULL)
		len_key = strlen(key);
	if (value != NULL)
		len_val = strlen(value);
	total_len = len_key + 1 + len_val + 1; // '=' + '\0'
	line = malloc(total_len);
	if (line == NULL)
		return (NULL);
	line[0] = '\0';
	if (key != NULL)
		ft_strcat(line, key);
	ft_strcat(line, "=");
	if (value != NULL)
		ft_strcat(line, value);
	return (line);
}

char	**env_to_array(t_env *env)
{
	int count;
	char **envp;
	int i;
	t_env *tmp;
	char *line;

	count = count_env(env);
	envp = malloc(sizeof(char *) * (count + 1));
	if (envp == NULL)
		return (NULL);
	i = 0;
	tmp = env;
	while (tmp != NULL)
	{
		line = kv_join(tmp->key, tmp->value);
		if (line == NULL)
		{
			while (i > 0)
			{
				i--;
				free(envp[i]);
			}
			free(envp);
			return (NULL);
		}
		envp[i] = line;
		i++;
		tmp = tmp->next;
	}
	envp[i] = NULL;
	return (envp);
}

char	*find_path_variable(char **envp)
{
	int i;

	i = 0;
	while (envp[i])
	{
		if (ft_strncmp(envp[i], "PATH=", 5) == 0)
			return (envp[i] + 5);
		i++;
	}
	return (NULL);
}

char	*join_with_slash(char *dir, char *cmd_path)
{
	char *full_path;
	int len;

	if (!dir || !cmd_path)
		return (NULL);
	len = ft_strlen(dir) + 1 + ft_strlen(cmd_path) + 1;
	full_path = malloc(len);
	if (!full_path)
		return (NULL);
	full_path[0] = '\0';
	ft_strcat(full_path, dir);
	ft_strcat(full_path, "/");
	ft_strcat(full_path, cmd_path);
	return (full_path);
}

char	*find_command_path(char *cmd, t_env *env)
{
	char *path_env;
	char **dirs;
	char *full_path;
	int i;
	char **envp;

	if (!cmd || cmd[0] == '\0')
		return (NULL);
	if (cmd[0] == '/' || cmd[0] == '.')
		return (ft_strdup(cmd));
	envp = env_to_array(env);
	if (!envp)
		return (NULL);
	path_env = find_path_variable(envp);
	if (!path_env)
	{
		free_dirs(envp);
		return (NULL);
	}
	dirs = ft_split(path_env, ':');
	if (!dirs)
	{
		free_dirs(envp);
		return (NULL);
	}
	i = 0;
	while (dirs[i])
	{
		full_path = join_with_slash(dirs[i], cmd);
		if (full_path && access(full_path, X_OK) == 0)
		{
			free_dirs(dirs);
			free_dirs(envp);
			return (full_path);
		}
		free(full_path);
		i++;
	}
	free_dirs(dirs);
	free_dirs(envp);
	return (NULL);
}

/*
Fonction	exec_builtin(cmd, env)

	Déclarer i, newline, cwd[1024](dossier courant ou le programme s execute),
		path

	Ignorer env pour l'instant (void)

	Si cmd est NULL ou cmd->argv est NULL ou cmd->argv[0] est NULL
		Retourner -1

	// ECHO
	Si cmd->argv[0] == "echo"
		i = 1
		newline = 1
		Si cmd->argv[1] existe et vaut "-n"
			newline = 0
			i = 2
		Tant que cmd->argv[i] existe
			Afficher cmd->argv[i]
			Si cmd->argv[i+1] existe
				Afficher un espace
			i = i + 1
		Fin tant que
		Si newline == 1
			Afficher un saut de ligne
		Retourner 0

	// PWD
	Si cmd->argv[0] == "pwd"
		Récupérer le chemin courant avec getcwd(cwd)
		Si getcwd réussi
			Afficher cwd + saut de ligne
			Retourner 0
		Sinon
			Retourner -1

	// CD
	Si cmd->argv[0] == "cd"
		Si cmd->argv[1] existe
			path = cmd->argv[1]
		Sinon
			path = getenv("HOME")
		Si chdir(path) échoue
			Afficher l'erreur avec perror
			Retourner -1
		Sinon
			Retourner 0

	// EXIT
	Si cmd->argv[0] == "exit"
		Quitter le programme avec exit(0)

	// Si aucune commande builtin trouvée
	Retourner -1
Fin fonction
*/

int	exec_cmd(t_cmd *cmd, t_env *env)
{
	pid_t pid;
	int status;
	char *cmd_path;
	char **envp;

	if (!cmd || !cmd->argv || !cmd->argv[0])
		return (-1);
	// if (exec_builtin(cmd, env) != -1)
	// 	return (0);
	pid = fork();
	if (pid < 0)
	{
		perror("fork");
		return (-1);
	}
	if (pid == 0)
	{
		if (setup_redirections(cmd) < 0)
			exit(1);
		cmd_path = find_command_path(cmd->argv[0], env);
		if (!cmd_path)
		{
			fprintf(stderr, "%s: command not found\n", cmd->argv[0]);
			exit(127);
		}
		envp = env_to_array(env);
		execve(cmd_path, cmd->argv, envp);
		perror("execve");
		exit(1);
	}
	waitpid(pid, &status, 0);
	return (WIFEXITED(status) ? WEXITSTATUS(status) : -1);
}

int	exec_pipeline(t_cmd *cmds, t_env *env)
{
	int pipefd[2];
	pid_t pid;
	int prev_fd;
	int status;
	t_cmd *current;
	char *cmd_path;
	char **envp;

	if (!cmds)
		return (-1);
	if (!cmds->next)
		return (exec_cmd(cmds, env));
	prev_fd = -1;
	current = cmds;
	while (current)
	{
		if (current->next && pipe(pipefd) < 0)
		{
			perror("pipe");
			return (-1);
		}
		pid = fork();
		if (pid < 0)
		{
			perror("fork");
			return (-1);
		}
		if (pid == 0)
		{
			if (prev_fd != -1)
			{
				dup2(prev_fd, STDIN_FILENO);
				close(prev_fd);
			}
			if (current->next)
			{
				close(pipefd[0]);
				dup2(pipefd[1], STDOUT_FILENO);
				close(pipefd[1]);
			}
			if (setup_redirections(current) < 0)
				exit(1);
			cmd_path = find_command_path(current->argv[0], env);
			if (!cmd_path)
			{
				fprintf(stderr, "%s: command not found\n", current->argv[0]);
				exit(127);
			}
			envp = env_to_array(env);
			execve(cmd_path, current->argv, envp);
			perror("execve");
			exit(1);
		}
		if (prev_fd != -1)
			close(prev_fd);
		if (current->next)
		{
			close(pipefd[1]);
			prev_fd = pipefd[0];
		}
		current = current->next;
	}
	while (wait(&status) > 0)
		;
	return (WIFEXITED(status) ? WEXITSTATUS(status) : -1);
}