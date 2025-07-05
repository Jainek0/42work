/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_pipe.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thcaquet <thcaquet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/01 15:15:10 by thcaquet          #+#    #+#             */
/*   Updated: 2025/07/05 16:36:59 by thcaquet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_token	*pipe_cut(t_data *data)
{
	t_token	*tmp;
	t_token	*new;

	new = data->first;
	while (new && new->type != 2)
	{
		tmp = new->next;
		free(new->str);
		free(new);
		new = tmp;
	}
	if (new)
	{
		tmp = new->next;
		free(new->str);
		free(new);
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

	new = data->first;
	first = data->first;
	old = 0;
	if (!data->first || data->first->type == PIPE)
		first = 0;
	while (new && new->type != PIPE)
	{
		old = new;
		new = new->next;
	}
	while (new)
	{
		tmp = new->next;
		free(new->str);
		free(new);
		new = tmp;
	}
	if (old)
		old->next = 0;
	data->first = first;
}

void	pipe_child(t_data *data, int p_old[2], int p_new[2], int i)
{
	int	j;

	j = 0;
	if (i != 0)
	{
		dup2(p_old[0], STDIN_FILENO);
		close(p_old[0]);
		close(p_old[1]);
	}
	if (i != data->pipe)
	{
		dup2(p_new[1], STDOUT_FILENO);
		close(p_new[0]);
		close(p_new[1]);
	}
	pipe_clear_last(data);
	shell_fonction_parse(data);
	close(data->std.in);
	close(data->std.out);
	free_data(data);
	exit(data->error);
}

void	pipe_parent(t_data *data, int p_old[2], int p_new[2], int i)
{
	if (i != 0)
	{
		close(p_old[0]);
		close(p_old[1]);
	}
	if (i < data->pipe)
	{
		p_old[0] = p_new[0];
		p_old[1] = p_new[1];
	}
}

void	mini_pipe(t_data *data)
{
	int	p_old[2];
	int	p_new[2];
	int	i;

	data->tab_pid_fork = malloc(sizeof(pid_t *) *(data->pipe + 1));
	if (!data->tab_pid_fork)
		liberate_all(data, MALLOC_FAILURE, 1);
	i = 0;
	while (i <= data->pipe)
	{
		shell_red_parse(data);
		if (i < data->pipe)
			pipe(p_new);
		data->tab_pid_fork[i] = set_fork(data);
		if (data->pid_fork == 0)
			pipe_child(data, p_old, p_new, i);
		else
			pipe_parent(data, p_old, p_new, i);
		++i;
		data->first = pipe_cut(data);
	}
	i = -1;
	while (++i <= data->pipe)
		waitpid(data->tab_pid_fork[i], NULL, 0);
}
