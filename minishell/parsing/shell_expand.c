/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_expand.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thcaquet <thcaquet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/17 04:18:35 by ledupont          #+#    #+#             */
/*   Updated: 2025/07/06 04:28:21 by thcaquet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	shell_exp_strcmp(char *envp, char *expand, int l)
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

int	shell_to_expand(t_data *data, char *s, int i)
{
	t_envlist	*cur;

	cur = data->start;
	while (cur)
	{
		if (shell_exp_strcmp(cur->str, data->ex, data->len) == 0)
		{
			i = shell_expanding(data, cur->str, s, i);
			return (i);
		}
		cur = cur->next;
	}
	i = shell_empty_expanding(data, s, i, data->len);
	return (i);
}

int	shell_expand_nutcase(t_data *data, char *s, int i)
{
	if (s[i] == '?')
		return (shell_error_expanding(data, s, i - 1));
	if (s[i] >= '0' && s[i] <= '9')
		return (shell_empty_expanding(data, s, i - 1, 1));
	return (i);
}

int	shell_expand(t_data *data, char *s, int i)
{
	int		j;
	int		k;

	j = i + 1;
	if (s[j] == '?' || (s[j] >= '0' && s[j] <= '9'))
		return (shell_expand_nutcase(data, s, j));
	while (ft_isalnum(s[j]) == 1 || s[j] == '_')
		j++;
	data->len = j - i - 1;
	data->ex = malloc(sizeof(char) * (data->len + 1));
	if (!data->ex)
		liberate_all(data, ERROR_MALLOC, 1);
	k = -1;
	j = i;
	while (++k < data->len)
		data->ex[k] = s[++j];
	data->ex[k] = '\0';
	i = shell_to_expand(data, s, i);
	return (i);
}
