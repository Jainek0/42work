/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_bis.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thcaquet <thcaquet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/02 14:29:43 by thcaquet          #+#    #+#             */
/*   Updated: 2025/07/02 16:37:57 by thcaquet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*str_random_eight(unsigned char *str)
{
	int	fd;
	int	i;

	i = 0;
	fd = open("/dev/urandom", O_RDONLY);
	read(fd, str, 8);
	while (i < 8)
	{
		if (!ft_isascii(str[i]))
			str[i] = str[i] / 2;
		if (!ft_isascii(str[i]))
			str[i] = 'a';
		++i;
	}
	str[17] = 0;
	close(fd);
	return ((char *) str);
}
