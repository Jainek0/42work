/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_parts.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ledupont <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 02:17:46 by ledupont          #+#    #+#             */
/*   Updated: 2024/11/06 02:17:58 by ledupont         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf_fd.h"

int	printf_fd_strlen(const char *s)
{
	int	i;

	i = 0;
	while (s[i])
		i ++;
	return (i);
}

int	printf_fd_putchar(char c, int fd)
{
	write(fd, &c, 1);
	return (1);
}

int	printf_fd_putstr(char *s, int fd)
{
	if (!s)
	{
		write(fd, "(null)", 6);
		return (6);
	}
	write(fd, s, printf_fd_strlen(s));
	return (printf_fd_strlen(s));
}

int	printf_fd_puthexa(unsigned long long n, char type, int fd)
{
	char	*uphex;
	char	*lowhex;
	int		l;

	l = 0;
	uphex = "0123456789ABCDEF";
	lowhex = "0123456789abcdef";
	if (n >= 16)
	{
		l = l + printf_fd_puthexa(n / 16, type, fd);
		l = l + printf_fd_puthexa(n % 16, type, fd);
	}
	else if (type == 'X')
		l = l + printf_fd_putchar(uphex[n], fd);
	else if (type == 'x')
		l = l + printf_fd_putchar(lowhex[n], fd);
	return (l);
}

int	printf_fd_putptr(void *ptr, int fd)
{
	size_t	loc;
	int		l;

	loc = (size_t) ptr;
	l = 0;
	if (!ptr)
		l = l + write (fd, "(nil)", 5);
	else
	{
		l = l + write(fd, "0x", 2);
		l = l + printf_fd_puthexa(loc, 'x', fd);
	}
	return (l);
}
