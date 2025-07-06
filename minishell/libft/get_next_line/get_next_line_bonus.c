/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thcaquet <thcaquet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/27 12:03:16 by thcaquet          #+#    #+#             */
/*   Updated: 2025/07/05 20:16:42 by thcaquet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../src/libft.h"

void	gnl_ft_free((void **)&char *buffer, char *nextl, char *scrap)
{
	ft_free((void **)&buffer);
	ft_free((void **)&nextl);
	scrap[0] = 0;
}

char	*get_read(int fd, char *scrap, char *buffer)
{
	char	*nextl;
	int		i;
	int		j;

	i = -1;
	nextl = gnl_dup(scrap);
	while (i == -1)
	{
		j = read(fd, buffer, BUFFER_SIZE);
		if (j == -1)
		{
			gnl_ft_free((void **)&buffer, nextl, scrap);
			return (0);
		}
		buffer[j] = 0;
		if (j == 0)
			break ;
		i = gnl_strchr(buffer, '\n');
		nextl = gnl_strjoin(nextl, buffer);
		if (!nextl)
			return (0);
	}
	gnl_rewrite(buffer, scrap, i);
	return (nextl);
}

char	*get_scrap(int fd, char *scrap, char *buffer)
{
	int		i;
	int		j;
	char	*nextl;

	i = gnl_strchr(scrap, '\0');
	j = gnl_strchr(scrap, '\n');
	if (i == 0 || j == -1)
		nextl = get_read(fd, scrap, buffer);
	else
	{
		ft_free((void **)&buffer);
		i = 0;
		nextl = malloc(j + 1);
		if (!nextl)
			return (0);
		nextl[0] = 0;
		while (i++ < j)
			nextl[i - 1] = scrap[i - 1];
		nextl[i - 1] = 0;
		gnl_rewrite(scrap, scrap, j);
	}
	return (nextl);
}

char	*get_next_line(int fd)
{
	static char	scrap[1024][BUFFER_SIZE + 1];
	char		*nextl;
	char		*buffer;

	if (fd < 0 || fd > 1024)
		return (0);
	buffer = malloc(BUFFER_SIZE + 1);
	if (!buffer)
		return (0);
	if (!scrap[fd][0])
		nextl = get_read(fd, scrap[fd], buffer);
	else
		nextl = get_scrap(fd, scrap[fd], buffer);
	if (nextl && !nextl[0])
	{
		ft_free((void **)&nextl);
		return (0);
	}
	return (nextl);
}
