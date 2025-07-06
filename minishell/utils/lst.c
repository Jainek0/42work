/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thcaquet <thcaquet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/21 19:04:05 by thcaquet          #+#    #+#             */
/*   Updated: 2025/07/06 02:22:37 by thcaquet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_envlist	*lst_add_front(t_envlist *env, char *content)
{
	t_envlist	*new;

	new = malloc(sizeof(t_envlist));
	if (!new)
		return (0);
	new->str = ft_strdup((const char *) content);
	if (!new->str)
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
	new->str = ft_strdup((const char *) content);
	if (!new->str)
		return ;
	old = env;
	while (old->next)
		old = old->next;
	old->next = new;
	new->next = 0;
}

void	lst_sort_str_tab(t_envlist **tab, int size)
{
	t_envlist	*tmp;
	int			i;

	i = 0;
	while (i < size)
	{
		if (tab[i] && i > 0 && env_comp(tab[i]->str, tab[i - 1]->str) < 0)
		{
			tmp = tab[i];
			tab[i] = tab[i - 1];
			tab[i - 1] = tmp;
			i -= 1;
		}
		else
			i++;
	}
}

int	lst_len(t_token *first)
{
	t_token	*node;
	int		i;

	if (!first)
		return (0);
	i = 0;
	node = first;
	while (node)
	{
		node = node->next;
		++i;
	}
	return (i);
}
