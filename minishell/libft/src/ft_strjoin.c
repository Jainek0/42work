/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thcaquet <thcaquet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/12 12:00:54 by thcaquet          #+#    #+#             */
/*   Updated: 2025/06/17 16:05:16 by thcaquet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*free_this(char *s1, char *s2, int free_nu)
{
	if (s1 && (free_nu == 10 || free_nu == 11))
		if (s1)
			free(s1);
	if (s2 && (free_nu == 1 || free_nu == 11))
		if (s2)
			free(s2);
	return (0);
}

char	*ft_strjoin(char *s1, char *s2, int free_nu)
{
	int		ls1;
	int		ls2;
	int		i;
	char	*str;

	ls1 = 0;
	ls2 = 0;
	if (s1)
		ls1 = ft_strlen(s1);
	if (s2)
		ls2 = ft_strlen(s2);
	i = -1;
	str = (char *) malloc(ls1 + ls2 + 1);
	if (!str)
		return (free_this(s1, s2, free_nu));
	while (++i < ls1)
		str[i] = s1[i];
	i--;
	while ((++i - ls1) < ls2)
		str[i] = s2[i - ls1];
	str[i] = 0;
	free_this(s1, s2, free_nu);
	return (str);
}
