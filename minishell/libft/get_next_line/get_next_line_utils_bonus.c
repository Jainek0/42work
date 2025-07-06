/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils_bonus.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thcaquet <thcaquet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/27 12:03:42 by thcaquet          #+#    #+#             */
/*   Updated: 2025/07/05 20:16:42 by thcaquet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../src/libft.h"

int	gnl_strchr(char *str, char chr)
{
	int	i;

	i = 0;
	while (chr == '\0' || str[i])
	{
		if (str[i] == chr)
		{
			if (chr == '\0')
				return (i);
			return (i + 1);
		}
		i++;
	}
	return (-1);
}

int	gnl_strlen(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '\n')
			return (i + 1);
		i++;
	}
	return (i);
}

char	*gnl_strjoin(char *s1, char *s2)
{
	int		l1;
	int		l2;
	int		ln;
	char	*new;

	if (!s1)
		l1 = 0;
	else
		l1 = gnl_strlen(s1);
	if (!s2)
		l2 = 0;
	else
		l2 = gnl_strlen(s2);
	new = malloc(l1 + l2 + 1);
	if (!new)
		return (0);
	ln = 0;
	while (ln++ < l1)
		new[ln - 1] = s1[ln - 1];
	ln = 0;
	while (ln++ < l2)
		new[l1 + ln - 1] = s2[ln - 1];
	new[l1 + l2] = 0;
	ft_free((void **)&s1);
	return (new);
}

void	gnl_rewrite(char *old, char *scrap, int j)
{
	int		i;

	i = gnl_strchr(old, '\0');
	if (i > j && j >= 0)
	{
		i = 0;
		while (old[j + i] && ++i)
			scrap[i - 1] = old[j + i - 1];
		scrap[i] = 0;
	}
	else
		scrap[0] = 0;
	if (scrap != old)
		ft_free((void **)&old);
}

char	*gnl_dup(char *str)
{
	int		i;
	char	*new;

	i = gnl_strlen(str);
	new = malloc(i + 1);
	if (!new)
		return (0);
	i = 0;
	while (str[i])
	{
		new[i] = str[i];
		i++;
	}
	new[i] = 0;
	return (new);
}
