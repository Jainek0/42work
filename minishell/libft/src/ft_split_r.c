/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_r.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thcaquet <thcaquet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/12 16:33:53 by thcaquet          #+#    #+#             */
/*   Updated: 2025/07/05 20:16:42 by thcaquet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	**free_all(char **tab)
{
	size_t	k;

	k = 0;
	while (tab[k])
		ft_free((void **)&tab[k++]);
	ft_free((void **)&tab[k]);
	ft_free((void **)&tab);
	return (NULL);
}

static size_t	cw(char const *str, char c)
{
	size_t	i;
	size_t	w;

	i = 0;
	w = 0;
	while (str[i])
	{
		if (str[i] != c && (!i || str[i - 1] == c))
			w++;
		i++;
	}
	return (w);
}

static void	ft_splited_split(char const *str, char c, char **new, char r)
{
	size_t	i;
	size_t	j;
	size_t	k;
	size_t	l;

	i = 0;
	k = 0;
	while (str[i] && k < cw(str, c))
	{
		j = 0;
		l = 0;
		while (str[i] == c && str[i])
			i++;
		while (str[i + j] != c && str[i + j])
			j++;
		new[k] = (char *) ft_calloc(j + 2, sizeof(char));
		if (!new[k])
			free_all(new);
		while (++l < j + 1 && ++i)
			new[k][l - 1] = str[(i - 1)];
		new[k][l - 1] = r;
		new[k][l] = 0;
		k++;
	}
	new[k] = NULL;
}

char	**ft_split_r(char const *str, char c, char r)
{
	char	**new;
	size_t	i;

	if (!str)
		return (NULL);
	i = cw(str, c);
	new = malloc(sizeof(char *) * (i + 1));
	if (!new)
		return (NULL);
	ft_splited_split(str, c, new, r);
	return (new);
}
