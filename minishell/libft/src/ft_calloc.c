/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thcaquet <thcaquet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/11 18:41:18 by thcaquet          #+#    #+#             */
/*   Updated: 2024/10/24 14:29:18 by thcaquet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t nmemb, size_t size)
{
	unsigned char	*dest;
	size_t			i;
	size_t			j;

	i = 0;
	if (size && nmemb > SIZE_MAX / size)
		return (0);
	dest = (unsigned char *) malloc(nmemb * size);
	if (! dest)
		return (NULL);
	while (nmemb--)
	{
		j = 0;
		while (j < size)
		{
			dest[i] = 0;
			j++;
			i++;
		}
	}
	return ((void *)dest);
}
