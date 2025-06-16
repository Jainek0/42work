/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ledupont <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/09 20:02:19 by ledupont          #+#    #+#             */
/*   Updated: 2024/10/09 20:02:21 by ledupont         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	unsigned char	*s1swap;
	unsigned char	*s2swap;

	s1swap = (unsigned char *)s1;
	s2swap = (unsigned char *)s2;
	while (n--)
	{
		if (*s1swap != *s2swap)
			return (*s1swap - *s2swap);
		s1swap++;
		s2swap++;
	}
	return (0);
}
