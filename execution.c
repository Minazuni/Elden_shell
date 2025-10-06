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


char	**env_to_array(t_env *env)
{
	char **envp;
	int i;
	int count;
	t_env *tmp;
	char *line;

	count = 0;
	tmp = env;
	while (tmp)
	{
		count++;
		tmp = tmp->next;
	}
	envp = malloc(sizeof(char *) * (count + 1));
	if (!envp)
		return (NULL);
	i = 0;
	tmp = env;
	while (tmp)
	{
		line = malloc(strlen(tmp->key) + strlen(tmp->value) + 2);
		sprintf(line, "%s=%s", tmp->key, tmp->value);
		envp[i++] = line;
		tmp = tmp->next;
	}
	envp[i] = NULL;
	return (envp);
}

char	*find_command_path(char *cmd, t_env *env)
{
	char *path_env;
	char *path;
	char *dir;
	char *full_path;
	t_env *tmp;

	if (!cmd || cmd[0] == '\0')
		return (NULL);
	if (cmd[0] == '/' || cmd[0] == '.')
		return (ft_strdup(cmd));
	tmp = env;
	path_env = NULL;
	while (tmp)
	{
		if (strcmp(tmp->key, "PATH") == 0)
		{
			path_env = tmp->value;
			break ;
		}
		tmp = tmp->next;
	}
	if (!path_env)
		return (NULL);
	path = ft_strdup(path_env);
	dir = strtok(path, ":");
	while (dir)
	{
		full_path = malloc(strlen(dir) + strlen(cmd) + 2);
		sprintf(full_path, "%s/%s", dir, cmd);
		if (access(full_path, X_OK) == 0)
		{
			free(path);
			return (full_path);
		}
		free(full_path);
		dir = strtok(NULL, ":");
	}
	free(path);
	return (NULL);
}

int	exec_builtin(t_cmd *cmd, t_env *env)
{
	int i;
	int newline;
	char cwd[1024];
	char *path;

	(void)env;
	if (!cmd || !cmd->argv || !cmd->argv[0])
		return (-1);
	if (strcmp(cmd->argv[0], "echo") == 0)
	{
		i = 1;
		newline = 1;
		if (cmd->argv[1] && strcmp(cmd->argv[1], "-n") == 0)
		{
			newline = 0;
			i = 2;
		}
		while (cmd->argv[i])
		{
			printf("%s", cmd->argv[i]);
			if (cmd->argv[i + 1])
				printf(" ");
			i++;
		}
		if (newline)
			printf("\n");
		return (0);
	}
	if (strcmp(cmd->argv[0], "pwd") == 0)
	{
		if (getcwd(cwd, sizeof(cwd)))
		{
			printf("%s\n", cwd);
			return (0);
		}
		return (-1);
	}
	if (strcmp(cmd->argv[0], "cd") == 0)
	{
		path = cmd->argv[1] ? cmd->argv[1] : getenv("HOME");
		if (chdir(path) < 0)
		{
			perror("cd");
			return (-1);
		}
		return (0);
	}
	if (strcmp(cmd->argv[0], "exit") == 0)
		exit(0);
	return (-1);
}

int	exec_cmd(t_cmd *cmd, t_env *env)
{
	pid_t pid;
	int status;
	char *cmd_path;
	char **envp;

	if (!cmd || !cmd->argv || !cmd->argv[0])
		return (-1);
	if (exec_builtin(cmd, env) != -1)
		return (0);
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