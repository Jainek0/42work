/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   liberate_all.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thcaquet <thcaquet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/24 18:15:12 by thcaquet          #+#    #+#             */
/*   Updated: 2025/07/02 18:30:11 by thcaquet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	mini_free_envlist(t_envlist *start)
{
	t_envlist	*clean;
	t_envlist	*ntc;

	clean = start;
	while (clean)
	{
		ntc = clean->next;
		if (clean->str)
			free(clean->str);
		free(clean);
		clean = 0;
		clean = ntc;
	}
}

void	mini_free_toklist(t_token *start)
{
	t_token	*clean;
	t_token	*ntc;

	clean = start;
	while (clean)
	{
		ntc = clean->next;
		if (clean->str)
			free(clean->str);
		free(clean);
		clean = 0;
		clean = ntc;
	}
}

void	free_data(t_data *data)
{
	if (data->start && data->start != NULL)
		mini_free_envlist(data->start);
	if (data->first && data->first != NULL)
		mini_free_toklist(data->first);
	if (data->line && data->line != NULL)
		free(data->line);
	if (data->tab_pid_fork && data->tab_pid_fork != NULL)
		free(data->tab_pid_fork);
}

void	mini_liberate_all(t_data *data, char *msg, int err)
{
	if (data)
		free_data(data);
	if (msg != NULL)
		printf("%s\n", msg);
	exit (err);
}
