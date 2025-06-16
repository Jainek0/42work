/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ledupont <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/15 21:52:56 by ledupont          #+#    #+#             */
/*   Updated: 2024/10/19 01:11:25 by ledupont         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	**ft_free(char **vm, int w)
{
	while (w--)
		free(vm[w]);
	free(vm);
	return (NULL);
}

static int	countword(char const *s, char c)
{
	int	i;
	int	w;

	i = 0;
	w = 0;
	while (s[i])
	{
		if (s[i] != c && (i == 0 || (i && s[i -1] == c)))
			w++;
		i++;
	}
	return (w);
}

static char	**sizeword(char const *s, char **vm, char c)
{
	int		i;
	int		w;
	int		l;

	i = 0;
	w = 0;
	l = 0;
	while (s[i])
	{
		if (s[i] != c && (i == 0 || (i && s[i -1] == c)))
			w++;
		if (s[i] != c)
			l++;
		i++;
		if ((s[i] == c && s[i - 1] != c) || (s[i] == 0 && s[i - 1] != c))
		{
			vm[w - 1] = ft_calloc(l + 1, sizeof(char));
			if (!vm[w - 1])
				return (ft_free(vm, w - 1));
			l = 0;
		}
	}
	return (vm);
}

static char	**copyword(char const *s, char **vm, char c)
{
	int		i;
	int		w;
	int		l;

	i = 0;
	w = 0;
	l = 0;
	while (s[i])
	{
		if (s[i] != c && (i == 0 || (i && s[i -1] == c)))
			w++;
		if (s[i] != c && w > 0)
		{
			vm[w - 1][l] = s[i];
			l++;
		}
		i++;
		if ((s[i] == c && s[i - 1] != c) || (s[i] == 0 && s[i - 1] != c))
			l = 0;
	}
	return (vm);
}

char	**ft_split(char const *s, char c)
{
	int		w;
	char	**vm;

	if (!s)
		return (NULL);
	w = countword(s, c);
	vm = malloc(sizeof(char *) * (w + 1));
	if (!vm)
		return (NULL);
	vm = sizeword(s, vm, c);
	if (vm)
	{
		vm = copyword(s, vm, c);
		vm[w] = NULL;
	}
	return (vm);
}
