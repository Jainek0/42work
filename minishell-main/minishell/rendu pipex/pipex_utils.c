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

void	pipex_free_all(char **path, char **cmd, char *cmdpath, int error)
{
	int	i;

	if (path && path != NULL)
	{
		i = -1;
		while (path[++i])
			free(path[i]);
		free(path);
	}
	if (cmd && cmd != NULL)
	{
		i = -1;
		while (cmd[++i])
			free(cmd[i]);
		free(cmd);
	}
	if (cmdpath && cmdpath != NULL)
		free(cmdpath);
	if (error > 0)
		exit (error);
}

int	pipex_fdcheck(char *argv, int type)
{
	if (type == 0 && access(argv, F_OK) != 0)
	{
		write(2, argv, ft_strlen(argv));
		write(2, ": no such file or directory\n", 28);
		return (1);
	}
	if (type == 0 && access(argv, R_OK) != 0)
	{
		write(2, argv, ft_strlen(argv));
		write(2, ": permission denied\n", 20);
		return (1);
	}
	if (type == 1 && access(argv, F_OK) == 0 && access(argv, W_OK) != 0)
	{
		write(2, argv, ft_strlen(argv));
		write(2, ": permission denied\n", 20);
		return (1);
	}
	return (0);
}

char	*pipex_cutpath(char *str, char **path)
{
	char	*realloc;
	int		l;
	int		i;

	l = ft_strlen(str);
	realloc = malloc(sizeof(char) * (l - 4));
	if (!realloc)
	{
		i = -1;
		while (path[++i])
			free(path[i]);
		free(path);
		exit (0);
	}
	i = -1;
	while (++i < l - 5)
		realloc[i] = str[i + 5];
	realloc[i] = '\0';
	free(str);
	return (realloc);
}

int	pipex_setpath(char **envp)
{
	int	i;

	i = 0;
	while (envp[i])
	{
		if (ft_strlen(envp[i]) > 5)
			if (envp[i][0] == 'P' && envp[i][1] == 'A' && envp[i][2] == 'T'
					&& envp[i][3] == 'H' && envp[i][4] == '=')
				return (i);
		i++;
	}
	return (-1);
}

char	*pipex_cmdpath(char *cmd, char *path)
{
	char	*cmdpath;
	int		i;
	int		j;

	i = ft_strlen(path);
	j = ft_strlen(cmd);
	if (j == 0)
		return (NULL);
	cmdpath = ft_calloc(1, i + j + 2);
	if (!cmdpath)
		return (NULL);
	i = -1;
	while (path[++i])
		cmdpath[i] = path[i];
	cmdpath[i++] = '/';
	j = 0;
	while (cmd[j])
		cmdpath[i++] = cmd[j++];
	cmdpath[i] = '\0';
	return (cmdpath);
}
