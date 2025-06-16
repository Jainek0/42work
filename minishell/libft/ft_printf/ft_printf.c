/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thcaquet <thcaquet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/19 15:36:51 by thcaquet          #+#    #+#             */
/*   Updated: 2025/04/03 17:30:31 by thcaquet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../src/libft.h"

static int	ft_s(unsigned char *ap)
{
	int	i;

	if (!ap)
		i = ft_putstrf_fd((unsigned char *) "(null)", 1);
	else
		i = ft_putstrf_fd(ap, 1);
	return (i);
}

static int	ft_p(unsigned long ap, char t)
{
	int	i;

	i = 0;
	if (t == 'p')
	{
		if (ap)
		{
			ft_putstrf_fd((unsigned char *) "0x", 1);
			i = ft_putnbrf_base(ap, "0123456789abcdef") + 2;
			return (i);
		}
		ft_putstrf_fd((unsigned char *) "(nil)", 1);
		return (5);
	}
	return (0);
}

static int	ft_switch(const char astr, va_list ap)
{
	int	i;

	i = 0;
	if (astr == 'c')
		i = ft_putcharf_fd(va_arg(ap, int), 1);
	else if (astr == '%')
		i = ft_putcharf_fd('%', 1);
	else if (astr == 's')
		i = ft_s(va_arg(ap, unsigned char *));
	else if (astr == 'p')
		i = ft_p(va_arg(ap, unsigned long), astr);
	else if (astr == 'i' || astr == 'd')
		i = ft_putnbrf_fd(va_arg(ap, unsigned long), 1);
	else if (astr == 'u')
		i = ft_putnbrf_base(va_arg(ap, unsigned int), "0123456789");
	else if (astr == 'x')
		i = ft_putnbrf_base(va_arg(ap, unsigned int), "0123456789abcdef");
	else if (astr == 'X')
		i = ft_putnbrf_base(va_arg(ap, unsigned int), "0123456789ABCDEF");
	return (i);
}

int	ft_printf(const char *astr, ...)
{
	int			i;
	int			j;
	int			k;		
	va_list		ap;

	i = 0;
	j = 0;
	va_start(ap, astr);
	while (astr[i])
	{
		k = 0;
		if (astr[i] == '%')
			k = ft_switch(astr[i + 1], ap);
		if (k || (astr[i] == '%' && astr[i + 1] == 's'))
		{
			i += 2;
			j += k;
		}
		else if (++j)
			ft_putcharf_fd(astr[i++], 1);
	}
	va_end(ap);
	return (j);
}
