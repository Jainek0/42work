/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thcaquet <thcaquet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/08 19:48:23 by thcaquet          #+#    #+#             */
/*   Updated: 2024/10/11 17:28:28 by thcaquet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	size_t	i;

	i = 0;
	if (!(dest) && !(src))
		return (0);
	if (src < dest)
	{
		while (i++ < n)
		{
			*(unsigned char *)(dest + n - i) = *(unsigned char *)(src + n - i);
		}
		return (dest);
	}
	return (ft_memcpy(dest, src, n));
}
