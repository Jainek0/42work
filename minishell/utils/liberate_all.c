/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   liberate_all.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thcaquet <thcaquet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/24 18:15:12 by thcaquet          #+#    #+#             */
/*   Updated: 2025/06/23 15:01:03 by thcaquet         ###   ########.fr       */
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
		if (clean->at)
			free(clean->at);
		free(clean);
		clean = 0;
		clean = ntc;
	}
}

void	free_data(t_data *data)
{
	if (data->start)
		mini_free_envlist(data->start);
}

void	mini_liberate_all(t_data *data, char *msg, int err)
{
	if (data->start && data->start != NULL)
		mini_free_envlist(data->start);
	if (data->line && data->line != NULL)
		free(data->line);
	if (msg != NULL)
		printf("%s\n", msg);
	exit (err);
}
