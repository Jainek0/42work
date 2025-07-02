/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_pipe.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thcaquet <thcaquet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/01 15:15:10 by thcaquet          #+#    #+#             */
/*   Updated: 2025/07/02 16:31:59 by thcaquet         ###   ########.fr       */
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
	tmp = new->next;
	free(new->str);
	free(new);
	new = tmp;
	return (new);
}

void	pipe_clear_last(t_data *data)
{
	t_token	*tmp;
	t_token	*new;
	t_token	*old;

	new = data->first;
	while (new && new->type != 2)
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
	old->next = 0;
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
	while (j < i)
	{
		data->first = pipe_cut(data);
		++j;
	}
	pipe_clear_last(data);				// test
	close(data->std.in);
	close(data->std.out);
	red_heredoc(data, "end");			// test
	printf("\npipe %d : \n\n", i);		// test
	print_tokens(data->first);			// test
	mini_liberate_all(data, "test", 0); // test
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

	if (data->pipe <= 0)
		return ;
	data->tab_pid_fork = malloc(sizeof(pid_t *) *(data->pipe + 1));
	if (!data->tab_pid_fork)
		mini_liberate_all(data, MALLOC_FAILURE, 1);
	i = 0;
	while (i <= data->pipe)
	{
		if (i < data->pipe)
			pipe(p_new);
		data->tab_pid_fork[i] = set_fork(data);
		if (data->pid_fork == 0)
			pipe_child(data, p_old, p_new, i);
		else
			pipe_parent(data, p_old, p_new, i);
		++i;
	}
	while (--i >= 0)
		waitpid(data->tab_pid_fork[i], NULL, 0);
	pipe_clear_last(data);
}
