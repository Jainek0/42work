/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_main.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ledupont <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 18:38:00 by ledupont          #+#    #+#             */
/*   Updated: 2025/02/18 20:05:36 by ledupont         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char	*pipex_cmdcheck(char **cmd, char **path)
{
	char	*cmdpath;
	int		i;

	if (access(cmd[0], X_OK) == 0 && access(cmd[0], F_OK) == 0)
		return (ft_strdup(cmd[0]));
	i = -1;
	while (path && path[++i])
	{
		cmdpath = pipex_cmdpath(cmd[0], path[i]);
		if (access(cmdpath, F_OK) == 0 && access(cmdpath, X_OK) == 0)
			return (cmdpath);
		else if (access(cmdpath, F_OK) == 0 && access(cmdpath, X_OK) != 0)
		{
			write(2, cmd[0], ft_strlen(cmd[0]));
			write(2, ": permission denied\n", 20);
			pipex_free_all(path, cmd, cmdpath, 1);
			exit (1);
		}
		free(cmdpath);
		cmdpath = NULL;
	}
	write(2, cmd[0], ft_strlen(cmd[0]));
	write(2, ": command not found\n", 20);
	pipex_free_all(path, cmd, NULL, 127);
	exit (127);
}

void	pipex_execute_cmd(t_tab node, char **argv, char **envp)
{
	if (ft_strlen(argv[node.i]) < 1)
	{
		write(2, ": permission denied\n", 20);
		pipex_free_all(node.path, NULL, NULL, 0);
		exit (1);
	}
	node.cmd = ft_split(argv[node.i], ' ');
	node.cmdpath = pipex_cmdcheck(node.cmd, node.path);
	if (node.cmdpath != NULL)
	{
		free(node.path);
		execve(node.cmdpath, node.cmd, envp);
		pipex_free_all(node.path, node.cmd, node.cmdpath, 1);
	}
	else
	{
		pipex_free_all(node.path, node.cmd, NULL, 1);
		exit (0);
	}
}

int	pipex_fork_process(t_tab node, char **argv, char **envp)
{
	if (pipe(node.pipefd) == -1)
		pipex_free_all(node.path, NULL, NULL, 1);
	node.pid = fork();
	if (node.pid == -1)
		pipex_free_all(node.path, NULL, NULL, 1);
	if (node.pid == 0)
	{
		if (dup2(node.in, STDIN_FILENO) == -1)
			pipex_free_all(node.path, NULL, NULL, 1);
		close(node.in);
		close(node.pipefd[FD_READ]);
		if (dup2(node.pipefd[FD_WRITE], STDOUT_FILENO) == -1)
			pipex_free_all(node.path, NULL, NULL, 0);
		close(node.pipefd[FD_WRITE]);
		pipex_execute_cmd(node, argv, envp);
	}
	close(node.in);
	node.in = node.pipefd[FD_READ];
	close(node.pipefd[FD_WRITE]);
	return (node.in);
}

int	pipex_parsing(t_tab node, int argc, char **argv, char **envp)
{
	pipex_fdcheck(argv[1], 0);
	node.in = open(argv[1], O_RDONLY);
	node.i = 1;
	while (++node.i < argc - 2)
		node.in = pipex_fork_process(node, argv, envp);
	node.pid = fork();
	if (node.pid == 0)
	{
		dup2(node.in, STDIN_FILENO);
		close(node.in);
		pipex_fdcheck(argv[argc - 1], 1);
		node.out = open(argv[argc - 1], O_CREAT | O_WRONLY | O_TRUNC, 0644);
		if (node.out < 0)
			pipex_free_all(node.path, NULL, NULL, 1);
		if (dup2(node.out, STDOUT_FILENO) == -1)
			pipex_free_all(node.path, NULL, NULL, 1);
		close(node.out);
		pipex_execute_cmd(node, argv, envp);
	}
	close(node.in);
	pipex_free_all(node.path, NULL, NULL, 0);
	while (waitpid(0, &node.wstatus, 0) != -1)
		if (WIFEXITED(node.wstatus))
			node.error = WEXITSTATUS(node.wstatus);
	return (node.error);
}
