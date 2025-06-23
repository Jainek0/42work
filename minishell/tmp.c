/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tmp.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thcaquet <thcaquet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/21 19:04:05 by thcaquet          #+#    #+#             */
/*   Updated: 2025/06/23 14:09:52 by thcaquet         ###   ########.fr       */
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

void	lst_add_back(t_envlist *env, char *content)
{
	t_envlist	*new;
	t_envlist	*old;
	
	new = malloc(sizeof(t_envlist));
	if (!new)
		return ;
	new->at = ft_strdup((const char *) content);
	if (!new->at)
		return ;
	old = env;
	while (old->next)
		old = old->next;
	old->next = new;
	new->next = 0;
}

