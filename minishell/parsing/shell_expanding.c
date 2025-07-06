/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_expanding.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thcaquet <thcaquet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/17 04:18:35 by ledupont          #+#    #+#             */
/*   Updated: 2025/07/06 04:35:42 by thcaquet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	shell_error_expanding(t_data *data, char *s, int i)
{
	char	*new;
	int		j;
	int		k;

	data->tmp = ft_itoa(data->error);
	if (!data->tmp)
		liberate_all(data, ERROR_MALLOC, 1);
	new = malloc(sizeof(char) * (ft_strlen(s)
				+ ft_strlen(data->tmp) - 1));
	if (!new)
		liberate_all(data, ERROR_MALLOC, 1);
	j = -1;
	while (++j < i)
		new[j] = s[j];
	k = 0;
	while (data->tmp[k])
		new[j++] = data->tmp[k++];
	k = i + 2;
	while (s[k])
		new[j++] = s[k++];
	new[j] = '\0';
	ft_free((void **)&data->tmp);
	ft_free((void **)&s);
	*data->sptr = new;
	return (i);
}

int	shell_empty_expanding(t_data *data, char *s, int i, int l)
{
	char	*new;
	int		j;
	int		n;

	n = ft_strlen(s) - l;
	new = malloc(sizeof(char) * (n + 1));
	if (!new)
		liberate_all(data, "malloc failure", 1);
	j = -1;
	while (++j < i)
		new[j] = s[j];
	n = i + l;
	while (s[++n])
		new[j++] = s[n];
	new[j] = '\0';
	ft_free((void **)&s);
	*data->sptr = new;
	return (i);
}

int	shell_expanding(t_data *data, char *cur, char *s, int i)
{
	char	*new;
	int		j;
	int		n;

	n = ft_strlen(s) + ft_strlen(cur) - (data->len * 2);
	new = malloc(sizeof(char) * (n + 1) + 1);
	if (!new)
		liberate_all(data, "malloc failure", 1);
	j = -1;
	while (++j < i)
		new[j] = s[j];
	n = i + data->len;
	while (cur[++data->len])
		new[j++] = cur[data->len];
	i = j - 1;
	while (s[++n])
		new[j++] = s[n];
	new[j] = '\0';
	ft_free((void **)&s);
	*data->sptr = new;
	return (i);
}
