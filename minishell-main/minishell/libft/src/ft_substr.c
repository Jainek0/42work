/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thcaquet <thcaquet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/12 11:06:41 by thcaquet          #+#    #+#             */
/*   Updated: 2024/10/20 19:26:36 by thcaquet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*str;
	size_t	ls;
	size_t	i;

	i = 0;
	if (!len || !s || (start > ft_strlen(s)))
	{
		str = ft_calloc(1, 1);
		return (str);
	}
	ls = ft_strlen(s);
	if ((ls - start) <= len)
		str = (char *) malloc((ls - start) + 1);
	else
		str = (char *) malloc(len + 1);
	if (!str)
		return (0);
	while (i < len && s[start + i])
	{
		str[i] = s[start + i];
		i++;
	}
	str[i] = 0;
	return (str);
}
