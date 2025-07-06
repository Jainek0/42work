/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   liberate_all.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thcaquet <thcaquet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/24 18:15:12 by thcaquet          #+#    #+#             */
/*   Updated: 2025/07/06 05:35:56 by thcaquet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	mini_free_envlist(t_envlist **start)
{
	t_envlist	*clean;
	t_envlist	*ntc;

	clean = *start;
	while (clean)
	{
		ntc = clean->next;
		if (clean->str)
			ft_free((void **)&clean->str);
		ft_free((void **)&clean);
		clean = ntc;
	}
	*start = NULL;
}

t_token	*mini_free_toklist(t_token **first)
{
	t_token	*clean;
	t_token	*ntc;

	clean = *first;
	while (clean)
	{
		ntc = clean->next;
		if (clean->str)
			ft_free((void **)&clean->str);
		ft_free((void **)&clean);
		clean = ntc;
	}
	*first = NULL;
	return (0);
}

void	free2dstr(char ***p_strs)
{
	char	**strs;
	int		i;

	i = 0;
	strs = *p_strs;
	if (!strs)
		return ;
	while (strs[i])
	{
		free(strs[i]);
		strs[i] = 0;
		++i;
	}
	free(strs);
	*p_strs = 0;
}

void	free_data(t_data *data)
{
	close(data->std.out);
	close(data->std.in);
	if (data->start && data->start != NULL)
		mini_free_envlist(&data->start);
	if (data->tok && data->tok != NULL)
		mini_free_toklist(&data->tok);
	if (data->line && data->line != NULL)
		ft_free((void **)&data->line);
	if (data->tab_pid_fork && data->tab_pid_fork != NULL)
		ft_free((void **)&data->tab_pid_fork);
	if (data->strs && data->strs != NULL)
		free2dstr((char ***)&data->strs);
	if (data->cmd && data->cmd != NULL)
		free2dstr((char ***)&data->cmd);
	if (data->tmp && data->tmp != NULL)
		ft_free((void **)&data->tmp);
	if (data->cnext && data->cnext != NULL)
		mini_free_toklist(&data->cnext);
	if (data->ex && data->ex != NULL)
		ft_free((void **)&data->ex);
	rl_clear_history();
}

void	liberate_all(t_data *data, char *msg, int err)
{
	if (data)
		free_data(data);
	if (msg != NULL)
		put_error(data, msg, err);
	exit (err);
}
