/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_n_realloc.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thcaquet <thcaquet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/24 19:26:36 by thcaquet          #+#    #+#             */
/*   Updated: 2025/07/05 20:16:42 by thcaquet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_n_realloc(char *str, int len)
{
	char	*new;
	int		i;

	i = -1;
	new = malloc(len + 1);
	if (!new)
		return (0);
	while (str[++i] && i < len)
		new[i] = str[i];
	while (i <= len)
		new[i++] = 0;
	if (str)
		ft_free((void **)&str);
	return (new);
}
