/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thcaquet <thcaquet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/10 13:25:51 by thcaquet          #+#    #+#             */
/*   Updated: 2024/10/11 15:32:12 by thcaquet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

// tab[0] = index / tab[i] = trus or fals 
char	*ft_strrchr(const char *s, int c)
{
	int		tab[2];
	char	r;
	char	*l;

	tab[0] = 0;
	tab[1] = 0;
	r = (char) c;
	l = (char *)s;
	if (r == 0)
		return ((char *)(s + ft_strlen((char *)s)));
	else
	{
		while (*(char *)(s + tab[0]))
		{
			if (*(char *)(s + tab[0]) == r)
			{
				l = (char *)(s + tab[0]);
				tab[1] = 1;
			}
			tab[0]++;
		}
	}
	if (tab[1])
		return (l);
	return (0);
}
