/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_export_add.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thcaquet <thcaquet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/06 02:53:09 by thcaquet          #+#    #+#             */
/*   Updated: 2025/07/06 05:08:15 by thcaquet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	export_add_bis(t_data *data, char *cmd, int i, char *old)
{
	char	**p_str;
	char	*str;

	if (!data->tmp)
		liberate_all(data, ERROR_MALLOC, 1);
	str = ft_strjoin(data->tmp, "=");
	if (!str)
		liberate_all(data, ERROR_MALLOC, 1);
	str = ft_clean_strjoin(str, old, 10);
	if (!str)
		liberate_all(data, ERROR_MALLOC, 1);
	str = ft_clean_strjoin(str, cmd + i + 2, 10);
	p_str = env_w_search(data, data->tmp);
	*p_str = str;
	ft_free((void **)&data->tmp);
}

void	mini_export_add(t_data *data, char *cmd, int i)
{
	char	*str;
	char	*old;

	if (data->tmp)
		ft_free((void **)&data->tmp);
	data->tmp = ft_strndup(cmd, i);
	old = env_get_search(data, data->tmp);
	if (!old)
	{
		str = ft_strjoin(data->tmp, cmd + i + 1);
		data->start = lst_add_front(data->start, str);
		free(str);
		return ;
	}
	export_add_bis(data, cmd, i, old);
}
