/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thcaquet <thcaquet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/20 13:59:20 by thcaquet          #+#    #+#             */
/*   Updated: 2024/10/20 19:00:51 by thcaquet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dest, char *src, size_t size)
{
	unsigned int	i;
	unsigned int	j;
	unsigned int	l;

	if (!dest && !*src)
		return (0);
	if (!dest && !size)
		return (ft_strlen(src));
	l = ft_strlen(dest);
	i = 0;
	j = 0;
	while (dest[i])
		i++;
	while (src[j] && i + 1 < size)
	{
		dest[i] = src[j];
		i++;
		j++;
	}
	dest[i] = '\0';
	if (i > size)
		return (ft_strlen(src) + size);
	return (ft_strlen(src) + l);
}
