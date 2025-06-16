/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ledupont <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/09 20:02:03 by ledupont          #+#    #+#             */
/*   Updated: 2024/10/09 20:02:06 by ledupont         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	unsigned char	*destswap;
	unsigned char	*srcswap;

	if (!dest && !src)
		return (NULL);
	if (dest <= src)
	{
		destswap = (unsigned char *)dest;
		srcswap = (unsigned char *)src;
		while (n--)
			*destswap++ = *srcswap++;
	}
	if (dest > src)
	{
		destswap = (unsigned char *)dest + n -1;
		srcswap = (unsigned char *)src + n -1;
		while (n--)
			*destswap-- = *srcswap--;
	}
	return (dest);
}
