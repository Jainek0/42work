/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thcaquet <thcaquet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/12 16:33:53 by thcaquet          #+#    #+#             */
/*   Updated: 2024/10/12 20:54:59 by thcaquet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	test(char const *s, char c, size_t i)
{
	if (s[i] != c && (!i || s[i - 1] == c))
		return ((size_t) 1);
	return ((size_t) 0);
}

static size_t	cw(char const *s, char c)
{
	size_t	i;
	size_t	w;

	i = 0;
	w = 0;
	while (s[i])
	{
		if (test(s, c, i))
			w++;
		i++;
	}
	return (w);
}

char	**ft_split(char const *s, char c)
{
	size_t	i;
	size_t	j;
	size_t	k;
	size_t	l;
	char	**str;

	i = 0;
	k = 0;
	str = malloc(sizeof(char *) * (cw(s, c) + 1));
	if (!str)
		return (0);
	while (s[i] && k < cw(s, c))
	{
		j = 0;
		l = 0;
		while (s[i] == c && s[i])
			i++;
		while (s[i + j] != c && s[i + j])
			j++;
		str[k++] = (char *) ft_calloc(j + 1, sizeof(char));
		while (++l < j + 1 && ++i)
			str[k - 1][l - 1] = s[(i - 1)];
	}
	str[k] = 0;
	return (str);
}
