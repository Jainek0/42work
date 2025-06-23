/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thcaquet <thcaquet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/12 12:00:54 by thcaquet          #+#    #+#             */
/*   Updated: 2025/06/23 16:07:42 by thcaquet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	int		ls1;
	int		ls2;
	int		i;
	char	*str;

	ls1 = 0;
	ls2 = 0;
	if (s1)
		ls1 = ft_strlen(s1);
	if (s2)
		ls2 = ft_strlen(s2);
	i = -1;
	str = (char *) malloc(ls1 + ls2 + 1);
	if (!str)
		return (0);
	while (++i < ls1)
		str[i] = s1[i];
	i--;
	while ((++i - ls1) < ls2)
		str[i] = s2[i - ls1];
	str[i] = 0;
	return (str);
}
