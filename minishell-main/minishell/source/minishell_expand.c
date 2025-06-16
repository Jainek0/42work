/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_expand.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leo <leo@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/17 04:18:35 by ledupont          #+#    #+#             */
/*   Updated: 2025/05/09 21:31:30 by leo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	mini_exp_strcmp(char *envp, char *expand, int l)
{
	int	i;

	i = 0;
	while (envp[i] && expand[i])
	{
		if (envp[i] != expand[i])
			return (1);
		if (envp[i + 1] == '=' && i == l - 1)
			return (0);
		i++;
	}
	return (1);
}

int	mini_to_expand(t_data *data, char *s, int i)
{
	t_envlist	*cur;

	cur = data->start;
	while (cur)
	{
		if (mini_exp_strcmp(cur->at, data->ex, data->len) == 0)
		{
			ft_free(data->ex);
			i = mini_expanding(data, cur->at, s, i);
			return (i);
		}
		cur = cur->next;
	}
	ft_free(data->ex);
	i = mini_empty_expanding(data, s, i, data->len);
	return (i);
}

int	mini_expand_nutcase(t_data *data, char *s, int i)
{
	if (s[i] == '?')
		return (mini_error_expanding(data, s, i - 1));
	if (s[i] >= '0' && s[i] <= '9')
		return (mini_empty_expanding(data, s, i - 1, 1));
	return (i);
}

int	mini_expand(t_data *data, char *s, int i)
{
	int		j;
	int		k;

	j = i + 1;
	if (s[j] == '?' || (s[j] >= '0' && s[j] <= '9'))
		return (mini_expand_nutcase(data, s, j));
	while (ft_isalnum(s[j]) == 1 || s[j] == '_')
		j++;
	data->len = j - i - 1;
	data->ex = malloc(sizeof(char) * (data->len + 1));
	if (!data->ex)
		mini_liberate_all(data, "malloc failure", 1);
	k = -1;
	j = i;
	while (++k < data->len)
		data->ex[k] = s[++j];
	data->ex[k] = '\0';
	i = mini_to_expand(data, s, i);
	return (i);
}
