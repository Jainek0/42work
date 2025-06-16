/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ledupont <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/07 12:34:50 by ledupont          #+#    #+#             */
/*   Updated: 2024/10/27 19:02:11 by ledupont         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_atoi(const char *nptr)
{
	int	result;
	int	neg;
	int	i;

	result = 0;
	i = 0;
	neg = 1;
	while ((nptr[i] && nptr[i] == ' ') || (nptr[i] >= '\t' && nptr[i] <= '\r'))
		i ++;
	if (nptr[i] == '-' || nptr[i] == '+')
	{
		if (nptr[i] == '-')
			neg = -neg;
		i ++;
	}
	while (nptr[i] >= '0' && nptr[i] <= '9')
	{
		result = (result * 10 + (nptr[i] - '0'));
		i ++;
	}
	return (neg * result);
}
