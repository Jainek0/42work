/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thcaquet <thcaquet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/12 12:21:25 by thcaquet          #+#    #+#             */
/*   Updated: 2024/10/12 17:25:29 by thcaquet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strtrim(char const *s1, char const *set)
{
	size_t	i;
	size_t	j;
	size_t	l;

	i = 0;
	l = ft_strlen(s1);
	while (s1[i++])
	{
		j = 0;
		while (s1[i - 1] != set[j] && set[j])
			j++;
		if (!set[j])
			break ;
	}
	while (s1[--l])
	{
		j = 0;
		while (s1[l] != set[j] && set[j])
			j++;
		if (!set[j])
			break ;
	}
	return (ft_substr(s1, i - 1, (l + 1) - (i - 1)));
}
