/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_expand.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thcaquet <thcaquet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/17 10:23:09 by thcaquet          #+#    #+#             */
/*   Updated: 2025/06/17 11:14:18 by thcaquet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

char	*other_expand(t_data *data, char *str, int *i)
{
	char	*new;

	new = 0;
	if (strncmp(&str[*i], "$$", 2) == 0)
	{
		new = ft_strndup(str, *i - 1);
		new = ft_strjoin(new, ft_itoa(getpid()), 11);
		new = ft_strjoin(new, &str[*i + 2], 1);
		*i += 2;
	}
	else if (strncmp(&str[*i], "$?", 2) == 0)
	{
		new = ft_strndup(str, *i - 1);
		new = ft_strjoin(new, ft_itoa(data->error), 11);
		new = ft_strjoin(new, &str[*i + 2], 1);
		*i += 2;
	}
	else
		new = str;
	return (new);
}

char	*hook_expand(t_data *data, char *str, int *i)
{
	int		j;
	char	*new;
	char	*search;

	j = 0;
	while (str[*i])
	{
		if (str[*i]== '$' && check_id_exp(str[*i + 1]))
		{
			while (str[*i + j + 1] && check_id_exp(str[*i + j + 1]))
				++j;
			new = ft_strndup(str, *i - 1);
			search = ft_strndup(&str[*i], j);
			new = ft_strjoin(new, env_get_search(data, search), 11);
			new = ft_strjoin(new, &str[*i + j], 1);
			*i += j;
		}
		else
			new = other_expand(data, str, i);
		++*i;
	}
	free(str);
	return (new);
}

char	*mini_expand(t_data *data, char *str)
{
	int		i;
	char	*new;

	i = 0;
	new = str;
	while (str[i])
	{
		if (str[i] == '$')
			new = hook_expand(data, str, &i);
		++i;
	}
	return (new);
}
