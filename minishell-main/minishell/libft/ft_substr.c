/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ledupont <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/15 21:52:00 by ledupont          #+#    #+#             */
/*   Updated: 2024/10/15 21:52:03 by ledupont         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	unsigned int	i;
	unsigned int	j;
	char			*sub;

	if (!s)
		return (NULL);
	i = start;
	j = 0;
	if (start >= (unsigned int)ft_strlen(s))
		return (ft_strdup(""));
	if (start + len > (unsigned int)ft_strlen(s))
		len = ft_strlen(s) - start;
	sub = malloc(sizeof(char) * (len + 1));
	if (!sub)
		return (NULL);
	while (i < start + len && i < (unsigned int)ft_strlen(s))
		sub[j++] = s[i++];
	sub[j] = 0;
	return (sub);
}
