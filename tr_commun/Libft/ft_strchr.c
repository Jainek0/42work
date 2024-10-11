/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thcaquet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/10 13:24:42 by thcaquet          #+#    #+#             */
/*   Updated: 2024/10/10 20:22:58 by thcaquet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *s, int c)
{
	int		i;
	char	r;

	r = (char) c;
	i = 0;
	if (r == 0)
		return ((char *)(s + ft_strlen((char *)s)));
	else
	{
		while (*(char *)(s + i))
		{
			if (*(char *)(s + i) == r)
				return ((char *)(s + i));
			i++;
		}
	}
	return (0);
}
