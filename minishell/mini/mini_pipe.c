/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_pipe.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thcaquet <thcaquet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/01 15:15:10 by thcaquet          #+#    #+#             */
/*   Updated: 2025/07/06 06:57:42 by thcaquet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_token	*pipe_cut(t_data *data)
{
	t_token	*tmp;
	t_token	*new;

	new = data->tok;
	while (new && new->type != 2)
	{
		tmp = new->next;
		ft_free((void **)&new->str);
		ft_free((void **)&new);
		new = tmp;
	}
	if (new)
	{
		tmp = new->next;
		ft_free((void **)&new->str);
		ft_free((void **)&new);
	}
	else
		tmp = 0;
	new = tmp;
	return (new);
}

void	pipe_clear_last(t_data *data)
{
	t_token	*tmp;
	t_token	*new;
	t_token	*old;
	t_token	*first;

	new = data->tok;
	first = data->tok;
	old = 0;
	if (!data->tok || data->tok->type == PIPE)
		first = 0;
	while (new && new->type != PIPE)
	{
		old = new;
		new = new->next;
	}
	while (new)
	{
		tmp = new->next;
		ft_free((void **)&new->str);
		ft_free((void **)&new);
		new = tmp;
	}
	if (old)
		old->next = 0;
	data->tok = first;
}

void	pipe_child(t_data *data, int i)
{
	int	j;

	j = 0;
	ft_free((void **)&data->tab_pid_fork);
	if (i != 0)
	{
		dup2(data->p_old[0], STDIN_FILENO);
		close(data->p_old[0]);
		close(data->p_old[1]);
	}
	if (i != data->pipe)
	{
		dup2(data->p_new[1], STDOUT_FILENO);
		close(data->p_new[0]);
		close(data->p_new[1]);
	}
	pipe_clear_last(data);
	shell_fonction_parse(data);
	close(data->std.in);
	close(data->std.out);
	free_data(data);
	exit(data->error);
}

void	pipe_parent(t_data *data, int i)
{
	if (i != 0)
	{
		close(data->p_old[0]);
		close(data->p_old[1]);
	}
	if (i < data->pipe)
	{
		data->p_old[0] = data->p_new[0];
		data->p_old[1] = data->p_new[1];
	}
}

void	mini_pipe(t_data *data)
{
	int	i;

	data->tab_pid_fork = malloc(sizeof(pid_t) *(data->pipe + 1));
	if (!data->tab_pid_fork)
		liberate_all(data, MALLOC_FAILURE, 1);
	i = 0;
	while (i <= data->pipe)
	{
		shell_red_parse(data);
		if (i < data->pipe)
			if (pipe(data->p_new))
				liberate_all(data, ERROR_PIPE, 1);
		data->tab_pid_fork[i] = set_fork(data);
		if (data->pid_fork == 0)
			pipe_child(data, i);
		else
			pipe_parent(data, i);
		++i;
		data->tok = pipe_cut(data);
		dup2(data->std.in, STDIN_FILENO);
		dup2(data->std.out, STDOUT_FILENO);
	}
	i = -1;
	while (++i <= data->pipe)
		waitpid(data->tab_pid_fork[i], NULL, 0);
	ft_free((void **)&data->tab_pid_fork);
}
