/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thcaquet <thcaquet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/12 11:06:41 by thcaquet          #+#    #+#             */
/*   Updated: 2024/10/12 16:48:14 by thcaquet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*str;
	size_t	ls;
	size_t	i;

	i = 0;
	ls = ft_strlen(s);
	if (!len || (start > ls))
	{
		str = (char *) malloc(1);
		str[i] = 0;
		return (str);
	}
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
