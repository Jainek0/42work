/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thcaquet <thcaquet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/12 16:33:53 by thcaquet          #+#    #+#             */
/*   Updated: 2025/07/05 20:16:42 by thcaquet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	**free_all(char **str)
{
	size_t	k;

	k = 0;
	while (str[k])
		ft_free((void **)&str[k++]);
	ft_free((void **)&str[k]);
	ft_free((void **)&str);
	return (NULL);
}

static size_t	cw(char const *s, char c)
{
	size_t	i;
	size_t	w;

	i = 0;
	w = 0;
	while (s[i])
	{
		if (s[i] != c && (!i || s[i - 1] == c))
			w++;
		i++;
	}
	return (w);
}

static void	ft_splited_split(char const *s, char c, char **str)
{
	size_t	i;
	size_t	j;
	size_t	k;
	size_t	l;

	i = 0;
	k = 0;
	while (s[i] && k < cw(s, c))
	{
		j = 0;
		l = 0;
		while (s[i] == c && s[i])
			i++;
		while (s[i + j] != c && s[i + j])
			j++;
		str[k] = (char *) ft_calloc(j + 1, sizeof(char));
		if (!str[k])
			free_all(str);
		while (++l < j + 1 && ++i)
			str[k][l - 1] = s[(i - 1)];
		k++;
	}
	str[k] = NULL;
}

char	**ft_split(char const *s, char c)
{
	char	**str;
	size_t	i;

	if (!s)
		return (NULL);
	i = cw(s, c);
	str = malloc(sizeof(char *) * (i + 1));
	if (!str)
		return (NULL);
	ft_splited_split(s, c, str);
	return (str);
}
