/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoll.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thcaquet <thcaquet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/05 13:45:14 by thcaquet          #+#    #+#             */
/*   Updated: 2025/07/06 02:16:22 by thcaquet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	calc(char *str, long long *res, int i, int *err)
{
	while (str[i] >= '0' && str[i] <= '9')
	{
		*res = (*res * 10) + (str[i++] - '0');
		if (res < 0)
			*err = 2;
	}
	if ((str[i]) && (str[i] < '0' || str[i] > '9') && (str[i] != ' '))
		*err = 2;
	if (*res > 9223372036854775807 || *res < -9223372036854775807)
		*err = 2;
}

long long	ft_atoll(char *str, int *err)
{
	int			i;
	long long	res;
	int			sign;

	i = 0;
	res = 0;
	sign = 0;
	if (str[i] == '-' || str[i] == '+')
	{
		sign++;
		i++;
	}
	if (((!ft_isdigit(str[i])) && (str[i + 1] != '-')) || ft_strlen(str) > 20)
		*err = 2;
	if (ft_strcmp(str, "-9223372036854775808") == 0)
	{
		*err = 0;
		return (0);
	}
	calc(str, &res, i, err);
	if (sign)
		res *= -1;
	return (res);
}
