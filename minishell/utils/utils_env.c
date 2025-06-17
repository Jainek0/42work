/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_env.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thcaquet <thcaquet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/21 16:45:53 by thcaquet          #+#    #+#             */
/*   Updated: 2025/06/17 15:57:45 by thcaquet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*env_get_search(t_data *data, char *re)
{
	char		*str;
	t_envlist	*node;

	node = data->start;
	if (!node)
		return (0);
	while (node && !check_research(node->at, re))
		node = node->next;
	if (node)
	{
		str = node->at;
		while (*str != '=' && str)
			++str;
		return (++str);
	}
	return (0);
}

char	*env_dup_search(t_data *data, char *re)
{
	char		*str;
	char		*new;
	t_envlist	*node;

	node = data->start;
	if (!node)
		return (0);
	while (node && !check_research(node->at, re))
		node = node->next;
	if (node)
	{
		str = node->at;
		while (*str != '=' && str)
			str++;
		new = ft_strdup(++str);
		if (!new)
			mini_liberate_all(data, MALLOC_FAILURE, 1);
		return (new);
	}
	return (0);
}

char	**env_w_search(t_data *data, char *re)
{
	t_envlist	*node;

	node = data->start;
	if (!node)
		return (0);
	while (node && !check_research(node->at, re))
		node = node->next;
	if (node)
	{
		free(node->at);
		return (&(node->at));
	}
	return (0);
}

