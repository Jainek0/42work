/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_put_fd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thcaquet <thcaquet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/15 17:19:38 by thcaquet          #+#    #+#             */
/*   Updated: 2025/04/03 17:30:30 by thcaquet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../src/libft.h"

int	ft_putcharf_fd(char c, int fd)
{
	write(fd, &c, 1);
	return (1);
}

static int	check_base(char *base)
{
	int	i;
	int	v;

	i = 0;
	while (base[i])
	{
		v = i + 1;
		while (base[v])
		{
			if (base[v] == base[i])
				return (0);
			v++;
		}
		if (base[i] == '+' || base[i] == '-')
			return (0);
		i++;
	}
	if (i <= 1)
		return (0);
	return (i);
}

int	ft_putnbrf_base(unsigned long nbr, char *base)
{
	unsigned int	b;
	int				i;

	i = 0;
	b = check_base(base);
	if (b < 2)
		return (0);
	if (nbr >= b)
		i += ft_putnbrf_base(nbr / b, base);
	write(1, &base[nbr % b], 1);
	return (++i);
}

int	ft_putnbrf_fd(int n, int fd)
{
	char	c;
	int		i;

	i = 0;
	if (n == -2147483648)
	{
		write(fd, "-2147483648", 11);
		return (11);
	}
	if (n < 0)
	{
		n = -n;
		write(fd, "-", 1);
		i ++;
	}
	if (n > 9)
		i += ft_putnbrf_fd((int) n / 10, fd);
	c = n % 10 + '0';
	write(fd, &c, 1);
	return (i + 1);
}

int	ft_putstrf_fd(unsigned char *s, int fd)
{
	int	i;

	i = 0;
	while (s[i])
		i++;
	write(fd, s, i);
	return (i);
}
