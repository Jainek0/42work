/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tmp.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thcaquet <thcaquet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/21 19:04:05 by thcaquet          #+#    #+#             */
/*   Updated: 2025/04/29 09:04:33 by thcaquet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_envlist	*lst_add_front(t_envlist *env, char *content)
{
	t_envlist	*new;

	new = malloc(sizeof(t_envlist));
	if (!new)
		return (0);
	new->at = ft_strdup((const char *) content);
	if (!new->at)
		return (0);
	new->next = env;
	return (new);
}

void	set_envs(t_data *data, char **envp)
{
	int			i;

	i = -1;
	if (!envp)
		return ;
	data->start = 0;
	while (envp[++i])
		data->start = lst_add_front(data->start, envp[i]);
}
