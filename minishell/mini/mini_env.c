/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thcaquet <thcaquet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/19 12:04:32 by thcaquet          #+#    #+#             */
/*   Updated: 2025/07/03 23:00:28 by thcaquet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	env_comp(char *str1, char *str2)
{
	while (*str1 && *str2 && *str1 != '=' && *str1 == *str2)
	{
		++str1;
		++str2;
	}
	return (*str1 - *str2);
}

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
		if (!data->start)
			mini_liberate_all(data, ERROR_MALLOC, 1);
	}
}

void	mini_env(t_data *data)
{
	t_envlist	*env;

	env = data->start;
	while (env)
	{
		if (check_print_env(env->str))
			printf("%s\n", env->str);
		env = env->next;
	}
	data->error = 0;
}

void	replace_old(t_data *data, char *cmd)
{
	t_envlist	*node;
	char		*old;
	char		**w_at;

	data->error = 0;
	node = env_search(data, "_");
	old = ft_strjoin("_=", cmd);
	if (!old)
		mini_liberate_all(data, ERROR_MALLOC, 1);
	if (!node)
	{
		lst_add_back(data->start, old);
		free(old);
	}
	else if (node->next)
	{
		env_unset(data, "_");
		lst_add_back(data->start, old);
		free(old);
	}
	else
	{
		w_at = env_w_search(data, "_");
		*w_at = old;
	}
}

void	last_cmd(t_data *data, char *cmd, char **t_cmd)
{
	char	**l_cmd;

	if (cmd)
		replace_old(data, cmd);
	else if (t_cmd)
	{
		while (*t_cmd)
		{
			l_cmd = t_cmd;
			++t_cmd;
		}
		replace_old(data, *l_cmd);
	}
	else
		replace_old(data, "");
}
