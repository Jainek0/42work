/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ledupont <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/08 12:18:02 by ledupont          #+#    #+#             */
/*   Updated: 2024/10/08 12:39:26 by ledupont         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	int	i;
	int	j;

	i = 0;
	j = -1;
	while (s[i])
	{
		if (s[i] == (unsigned char)c)
			j = i;
		i ++;
	}
	if (j >= 0)
		return ((char *)s + j);
	if ((unsigned char)c == 0)
		return ((char *)s + i);
	return (NULL);
}
