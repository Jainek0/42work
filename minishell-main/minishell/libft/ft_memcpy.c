/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ledupont <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/09 20:00:44 by ledupont          #+#    #+#             */
/*   Updated: 2024/10/09 20:00:52 by ledupont         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	unsigned char	*destswap;
	unsigned char	*srcswap;

	if (!dest && !src)
		return (NULL);
	srcswap = (unsigned char *)src;
	destswap = (unsigned char *)dest;
	while (n--)
		*destswap++ = *srcswap++;
	return (dest);
}
