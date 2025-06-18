/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_expand.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thcaquet <thcaquet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/17 10:23:09 by thcaquet          #+#    #+#             */
/*   Updated: 2025/06/18 15:17:38 by thcaquet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

char	*other_expand(t_data *data, char *old, int *i)
{
	char	*new;

	new = 0;
	new = ft_strndup(old, *i);
	if (strncmp(&old[*i], "$$", 2) == 0)
	{
		new = ft_strjoin(new, ft_itoa(getpid()), 11);
		new = ft_strjoin(new, &old[*i + 2], 10);
		*i += ft_intlen(getpid()) + 1;
	}
	else if (strncmp(&old[*i], "$?", 2) == 0)
	{
		new = ft_strjoin(new, ft_itoa(data->error), 11);
		new = ft_strjoin(new, &old[*i + 2], 10);
		*i += ft_intlen(data->error) + 1;
	}
	else
	{
		new = ft_strjoin(new, &old[*i], 10);
		++*i;
	}
	free(old);
	return (new);
}

char	*hook_expand(t_data *data, char *old, int *i)
{
	int		j;
	int		k;
	char	*new;
	char	*search;
	char	*tmp;

	j = 1;
	k = 0;
	while (old[*i + j + 1] && check_id_exp(old[*i + j + 1]))
		++j;
	new = ft_strndup(old, *i);
	search = ft_strndup(&old[*i + 1], j);
	tmp = env_get_search(data, search);
	free(search);
	if (tmp)
	{
		k = strlen(tmp);
		new = ft_strjoin(new, tmp, 10);
	}
	new = ft_strjoin(new, &old[*i + j + 1], 10);
	free (old);
	*i += k;
	return (new);
}

char	*mini_expand(t_data *data, char *str)
{
	int		i;
	char	*w_str;

	i = 0;
	w_str = ft_strdup(str);
	free(str);
	while (w_str[i])
	{
		if (w_str[i] == '$' && check_id_exp(w_str[i + 1]))
			w_str = hook_expand(data, w_str, &i);
		else if (w_str[i] == '$')
			w_str = other_expand(data, w_str, &i);
		else
			++i;
	}
	return (w_str);
}
