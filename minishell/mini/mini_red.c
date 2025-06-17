/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_red.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thcaquet <thcaquet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/01 19:33:33 by thcaquet          #+#    #+#             */
/*   Updated: 2025/06/17 11:22:47 by thcaquet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	red_truncate(t_data *data, char *file)
{
	data->fd.out = open(file, O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if (data->fd.out < 0)
	{
		put_error(data, OPEN_FAILURE, 1);
		data->error = 128;
		return ;
	}
	dup2(data->fd.out, STDOUT_FILENO);
	close(data->fd.out);
	data->error = 0;
}

void	red_append(t_data *data, char *file)
{
	if (access(file, F_OK) == 0 && access(file, W_OK) == -1)
	{
		put_error(data, ERROR_FILE_PERM, 1);
		data->error = 126;
		return ;
	}
	data->fd.out = open(file, O_CREAT | O_WRONLY | O_APPEND, 0644);
	if (data->fd.out < 0)
	{
		put_error(data, OPEN_FAILURE, 1);
		data->error = 128;
		return ;
	}
	dup2(data->fd.out, STDOUT_FILENO);
	close(data->fd.out);
	data->error = 0;
}

void	red_read(t_data *data, char *file)
{
	if (access(file, F_OK))
	{
		put_error(data, ERROR_FILE_PATH, 1);
		data->error = 126;
		return ;
	}
	else if (access(file, R_OK))
	{
		put_error(data, ERROR_FILE_PERM, 1);
		data->error = 127;
		return ;
	}
	data->fd.in = open(file, O_RDONLY);
	if (data->fd.in < 0)
	{
		put_error(data, OPEN_FAILURE, 1);
		data->error = 128;
		return ;
	}
	dup2(data->fd.in, STDIN_FILENO);
	close(data->fd.in);
	data->error = 0;
}

void	hook_heredoc(t_data *data, char *end)
{
	char	*line;
	char	*tmp;

	while (1)
	{
		line = readline("> ");
		tmp = 0;
		if (!ft_strcmp(line, end))
			break ;
		tmp = ft_strrchr(line, '$');
		while (tmp)
		{
			mini_expand(data, tmp);
			tmp = ft_strrchr(tmp, '$');
		}
		write(data->fd.out, line, strlen(line));
		write(data->fd.out, "\n", 1);
		free(line);
	}
	free(line);
}

void	red_heredoc(t_data *data, char *end)
{
	char	*file;
	int		i;

	i = 0;
	file = 0;
	data->error = 0;
	while (!file || access(file, F_OK) != -1)
	{
		if (file)
			free(file);
		file = ft_strjoin("heredoc_tmp_", ft_itoa(i++), 1);
	}
	data->fd.in = open(file, O_CREAT | O_WRONLY | O_TRUNC, 0644);
	dup2(data->fd.in, STDIN_FILENO);
	close(data->fd.in);
	hook_heredoc(data, end);
	free(file);
}
