/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ledupont <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/05 15:06:48 by ledupont          #+#    #+#             */
/*   Updated: 2024/11/06 01:49:40 by ledupont         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_FD_H

# define FT_PRINTF_FD_H

# include <unistd.h>
# include <stdarg.h>

int	ft_printf_fd(int fd, const char *s, ...);
int	printf_fd_putchar(char c, int fd);
int	printf_fd_putnbr(int n, int fd);
int	printf_fd_puthexa(unsigned long long n, char type, int fd);
int	printf_fd_putnbrui(unsigned int n, int fd);
int	printf_fd_putptr(void *ptr, int fd);
int	printf_fd_putstr(char *s, int fd);
int	printf_fd_strlen(const char *s);

#endif
