/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strndup.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thcaquet <thcaquet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/17 10:07:14 by thcaquet          #+#    #+#             */
/*   Updated: 2025/07/02 16:39:12 by thcaquet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strndup(char *str, int size)
{
	char	*new;
	int		i;

	i = 0;
	if (size < 0)
		return (0);
	new = malloc(size + 1);
	if (!new)
		return (0);
	while (str[i] && i < size)
	{
		new[i] = str[i];
		i++;
	}
	while (i <= size)
		new[i++] = 0;
	new[size] = 0;
	return (new);
}
