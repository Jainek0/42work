/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ledupont <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/09 20:02:31 by ledupont          #+#    #+#             */
/*   Updated: 2024/10/09 20:02:33 by ledupont         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	const unsigned char	*sswap;

	sswap = s;
	while (n--)
	{
		if (*sswap == (unsigned char)c)
			return ((void *)sswap);
		sswap++;
	}
	return (NULL);
}
