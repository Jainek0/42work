/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_liberator.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leo <leo@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/17 04:18:35 by ledupont          #+#    #+#             */
/*   Updated: 2025/05/09 22:03:48 by leo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_free(void *ptr)
{
	free(ptr);
	ptr = NULL;
}

void	mini_invalid_line(char *str, char *msg)
{
	if (str && str != NULL)
		ft_free(str);
	if (msg)
		printf("Error : %s\n", msg);
}

void	free2dstr(char **strs)
{
	int	i;

	i = 0;
	while (strs && strs[i])
		ft_free(strs[i++]);
	ft_free(strs);
}

void	mini_free_envlist(t_envlist *start)
{
	t_envlist	*clean;
	t_envlist	*ntc;

	clean = start;
	while (clean)
	{
		ntc = clean->next;
		if (clean->at)
			ft_free(clean->at);
		ft_free(clean);
		clean = ntc;
	}
	clean = NULL;
}

void	mini_liberate_all(t_data *data, char *msg, int err)
{
	if (data->ltab && data->ltab != NULL)
		free2dstr(data->ltab);
	if (data->story && data->story != NULL)
		ft_free(data->story);
	if (data->tmp && data->tmp != NULL)
		ft_free(data->tmp);
	if (data->start && data->start != NULL)
		mini_free_envlist(data->start);
	if (data->line && data->line != NULL)
		ft_free(data->line);
	if (err > 0)
		printf("Error : ");
	if (msg != NULL)
		printf("%s\n", msg);
	exit (err);
}
