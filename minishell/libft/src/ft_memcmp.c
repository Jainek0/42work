/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thcaquet <thcaquet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/10 16:59:20 by thcaquet          #+#    #+#             */
/*   Updated: 2024/10/11 17:16:56 by thcaquet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	size_t	i;

	i = 0;
	if (n == 0)
		return (0);
	while (*(unsigned char *)(s1 + i) == *(unsigned char *)(s2 + i))
	{
		if (n == 0 || i == n - 1)
			break ;
		i++;
	}
	return (*(unsigned char *)(s1 + i) - *(unsigned char *)(s2 + i));
}
