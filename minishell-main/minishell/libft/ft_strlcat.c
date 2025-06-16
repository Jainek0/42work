/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ledupont <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/09 18:17:47 by ledupont          #+#    #+#             */
/*   Updated: 2024/10/09 18:17:50 by ledupont         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t	l;
	size_t	i;
	size_t	j;

	if ((!dst || !src) && size == 0)
		return (ft_strlen(src));
	l = ft_strlen(dst);
	i = l;
	j = 0;
	if (size == 0)
		return (ft_strlen(src));
	if (size < l)
		return (size + ft_strlen(src));
	while (i < size -1 && src[j])
	{
		dst[i] = src[j];
		i ++;
		j ++;
	}
	dst[i] = 0;
	return (l + ft_strlen(src));
}
