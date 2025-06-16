/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thcaquet <thcaquet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/10 13:25:51 by thcaquet          #+#    #+#             */
/*   Updated: 2025/04/29 08:52:06 by thcaquet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	int		i;
	int		l;
	char	r;

	r = (char) c;
	l = ft_strlen((char *)s);
	i = 1;
	if (r == 0)
		return ((char *)(s + l));
	while (l >= i)
	{
		if (*(char *)(s + l - i) == r)
			return ((char *)(s + l - i));
		i++;
	}
	return (0);
}
