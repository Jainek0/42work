/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ledupont <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/15 21:52:20 by ledupont          #+#    #+#             */
/*   Updated: 2024/10/15 21:52:23 by ledupont         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	int		l;
	char	*s;

	if (!s1 || !s2)
		return (NULL);
	l = ft_strlen(s1) + ft_strlen(s2);
	s = malloc(sizeof(char) * l + 1);
	if (!s)
		return (NULL);
	ft_strlcpy(s, s1, ft_strlen(s1) +1);
	ft_strlcpy(s + ft_strlen(s1), s2, ft_strlen(s2) +1);
	return (s);
}
