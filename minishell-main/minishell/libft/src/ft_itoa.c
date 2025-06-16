/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thcaquet <thcaquet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/13 12:38:10 by thcaquet          #+#    #+#             */
/*   Updated: 2024/10/13 14:16:07 by thcaquet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	s_int(int n)
{
	size_t	i;

	i = 0;
	if (n < 0)
		i++;
	while (n != 0 && ++i)
		n /= 10;
	return (i);
}

char	*ft_itoa(int n)
{
	char			*str;
	size_t			s;
	unsigned int	u_n;

	s = s_int(n);
	u_n = n;
	if (n == 0)
		s++;
	str = ft_calloc(s + 1, 1);
	if (!str)
		return (0);
	if (n < 0)
		u_n = -n;
	while (s)
	{
		str[--s] = (u_n % 10 + '0');
		u_n /= 10;
	}
	if (n < 0)
		str[0] = '-';
	return (str);
}
