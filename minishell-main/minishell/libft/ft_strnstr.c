/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ledupont <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/08 10:04:23 by ledupont          #+#    #+#             */
/*   Updated: 2024/10/08 10:23:27 by ledupont         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	unsigned long	i;
	unsigned long	j;

	i = 0;
	if ((!big || !little) && !len)
		return (0);
	if (little[i] == '\0')
		return ((char *)big);
	while (big[i] != '\0' && i <= len)
	{
		j = 0;
		while ((little[j] == big[i + j]) && little[j] && (i + j) < len)
		{
			j ++;
			if (little[j] == '\0')
				return ((char *)big + i);
		}
		i ++;
	}
	return (0);
}
