/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_execve.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thcaquet <thcaquet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/28 14:57:44 by thcaquet          #+#    #+#             */
/*   Updated: 2025/07/04 15:43:15 by thcaquet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*check_path(char **all_path, char *cmd)
{
	char	*path;

	if (!all_path || !*all_path)
		return (0);
	path = ft_clean_strjoin(*all_path, cmd, 0);
	while (*all_path && access(path, F_OK) == -1)
	{
		free(path);
		path = ft_clean_strjoin(*all_path++, cmd, 0);
	}
	return (path);
}

void	exec_path(t_data *data, char **all_path, char **cmd, char **envp)
{
	char	*path;

	path = check_path(all_path, cmd[0]);
	if (!path || access(path, F_OK) == -1)
		put_error(data, ERROR_EXEC_CMD, 0);
	else if (access(path, X_OK) == -1)
		put_error(data, ERROR_PERM, 0);
	else
	{
		free_tab(all_path);
		free_data(data);
		execve(path, cmd, envp);
	}
	if (path)
		free(path);
}

void	exec_fork(t_data *data, char **all_path, char **cmd)
{
	char	**envp;

	envp = lst_to_tab(data);
	if (cmd[0] && ft_strrchr(cmd[0], '/'))
	{
		if (access(cmd[0], F_OK) == -1)
			put_error(data, ERROR_EXEC_PATH, 127);
		else if (access(cmd[0], X_OK) == -1)
			put_error(data, ERROR_PERM, 0);
		else
		{
			free_tab(all_path);
			free_data(data);
			execve(cmd[0], cmd, envp);
		}
	}
	else
		exec_path(data, all_path, cmd, envp);
	free_tab(envp);
	if (all_path)
		free_tab(all_path);
	free_data(data);
	free2dstr(cmd);
	exit(127);
}

void	mini_execve(t_data *data, char **cmd)
{
	char	**all_path;
	int		status;

	(void) data;
	last_cmd(data, NULL, cmd);
	if (ft_strcmp("", cmd[0]) == 0 && cmd[1] == 0)
	{
		printf("%s", ERROR_EXEC_CMD);
		data->error = 127;
		return ;
	}
	if (data->pipe == 0)
		set_fork(data);
	all_path = ft_split_r(env_get_search(data, "PATH"), ':', '/');
	if (data->pid_fork == 0)
		exec_fork(data, all_path, cmd);
	else
	{
		if (all_path)
			free_tab(all_path);
		waitpid(data->pid_fork, &status, 0);
		data->error = (status >> 8) & 0xFF;
	}
}
