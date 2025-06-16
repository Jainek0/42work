/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ledupont <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/15 21:53:12 by ledupont          #+#    #+#             */
/*   Updated: 2024/10/15 21:53:13 by ledupont         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	countsize(int n)
{
	int	l;

	l = 0;
	if (n == 0)
		return (1);
	if (n < 0)
	{
		l++;
		n = -n;
	}
	while (n > 0)
	{
		n = n / 10;
		l++;
	}
	return (l);
}

static char	*fillit(char *it, int n, int l)
{
	it[l] = 0;
	l--;
	if (n == 0)
	{
		it[0] = '0';
		return (it);
	}
	if (n < 0)
	{
		it[0] = '-';
		n = -n;
	}
	while (n > 0)
	{
		it[l] = n % 10 + '0';
		n = n / 10;
		l--;
	}
	return (it);
}

char	*ft_itoa(int n)
{
	int		l;
	char	*it;

	l = countsize(n);
	if (n == -2147483648)
		return (ft_strdup("-2147483648"));
	it = malloc(sizeof(char) * (l + 1));
	if (!it)
		return (NULL);
	it = fillit(it, n, l);
	return (it);
}
