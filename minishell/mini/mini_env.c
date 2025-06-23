/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thcaquet <thcaquet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/19 12:04:32 by thcaquet          #+#    #+#             */
/*   Updated: 2025/06/23 14:13:58 by thcaquet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	set_envs(t_data *data, char **envp)
{
	int			i;

	if (!envp)
		return ;
	data->start = 0;
	i = -1;
	while (envp[++i])
	{
		data->start = lst_add_front(data->start, envp[i]);
		// if (!data->start)
		// 	mini_liberate_all(data, , );
	}
}

void	mini_env(t_data *data)
{
	t_envlist	*env;

	env = data->start;
	while (env)
	{
		printf("%s\n", env->at);
		env = env->next;
	}
	data->error = 0;
}

void    mini_unset(t_data *data, char *str)
{
	t_envlist   *node;
	t_envlist   *lst;

	data->error = 0;
	lst = data->start;
	node = env_search(data, str);
	if (!node)
		return ;
	while (lst->next != node)
		lst = lst->next;
	lst->next = node->next;
	free(node->at);
	free(node);
}

void    last_cmd(t_data *data, char *cmd)
{
	t_envlist   *node;
	char		*old;

	data->error = 0;
	node = env_search(data, cmd);
	old = ft_strjoin("_=", cmd);
	if (!old)
		mini_liberate_all(data, ERROR_MALLOC, 1);
	if (!node)
		lst_add_back(data->start, old);
	else if (node->next)
	{
		mini_unset(data, "_");
		if (!old)
			mini_liberate_all(data, ERROR_MALLOC, 1);
		lst_add_back(data->start, old);
	}
}


