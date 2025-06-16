/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thcaquet <thcaquet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/10 15:58:25 by thcaquet          #+#    #+#             */
/*   Updated: 2025/04/04 18:15:50 by thcaquet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	space(const char c)
{
	return ((c == ' ' ) || (c >= 9 && c <= 13));
}

static int	ft_space(const char *str)
{
	int	i;

	i = 0;
	while (space(str[i]))
		i++;
	return (i);
}

int	ft_atoi(const char *str)
{
	int	i;
	int	nb;
	int	s;

	s = 1;
	nb = 0;
	i = ft_space(str);
	if (str[i] == '-')
	{
		i++;
		s = -1;
	}
	else if (str[i] == '+')
		i++;
	while (ft_isdigit(str[i]))
		nb = nb * 10 + (str[i++] - '0');
	return (nb * s);
}
