/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ledupont <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/30 12:19:51 by ledupont          #+#    #+#             */
/*   Updated: 2024/11/13 21:14:55 by ledupont         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

void	gnl_bufset(char *buffer)
{
	int	i;
	int	j;

	i = 0;
	while (*(buffer + i) != '\n' && *(buffer + i) != '\0' && i < BUFFER_SIZE)
		i++;
	i++;
	j = 0;
	while (*(buffer + i) != '\0' && i < BUFFER_SIZE)
		*(buffer + j++) = *(buffer + i++);
	while (j < BUFFER_SIZE)
		*(buffer + j++) = '\0';
	return ;
}

char	*gnl_bufjoin(char *line, char *buffer, int size)
{
	char	*new;
	int		i;
	int		j;

	i = 0;
	while (line && *(line + i) != '\0')
		i++;
	new = malloc(sizeof(char) * (i + size + 1));
	if (!new)
		return (gnl_freeline(line));
	j = 0;
	while (j < i)
	{
		*(new + j) = *(line + j);
		j++;
	}
	i = 0;
	while (i < size)
	{
		*(new + (j + i)) = *(buffer + i);
		i++;
	}
	*(new + (j + i)) = '\0';
	free(line);
	return (new);
}

char	*gnl_lineset(char *buffer, int jump)
{
	char	*line;
	int		i;

	line = malloc(sizeof(char) * (jump + 1));
	if (!line)
		return (NULL);
	i = 0;
	while (i < jump)
	{
		*(line + i) = *(buffer + i);
		i++;
	}
	*(line + jump) = '\0';
	return (line);
}

char	*gnl_crossroad(char *line, int fd, char *buffer, int jump)
{
	int	i;
	int	put;

	while (line && (jump == -1 || *line == 0 || *(buffer + (jump - 1)) != 10))
	{
		put = read(fd, buffer, BUFFER_SIZE);
		if (put < 0)
			return (gnl_freeline(line));
		if (put == 0)
			return (line);
		i = 0;
		while (put + i < BUFFER_SIZE)
			*(buffer + (put + i++)) = '\0';
		jump = gnl_endline(buffer);
		if (jump == -1)
		{
			line = gnl_bufjoin(line, buffer, put);
			gnl_bufset(buffer);
		}
		else
			line = gnl_bufjoin(line, buffer, jump);
	}
	return (line);
}

char	*get_next_line(int fd)
{
	static char	buffer[BUFFER_SIZE + 1] = {0};
	char		*line;
	int			jump;

	if (fd < 0 || BUFFER_SIZE < 1 || fd > 1024)
		return (NULL);
	jump = gnl_endline(buffer);
	line = gnl_lineset(buffer, jump);
	if (!line)
		return (NULL);
	line = gnl_crossroad(line, fd, buffer, jump);
	gnl_bufset(buffer);
	if (line && *line == '\0')
	{
		free(line);
		return (NULL);
	}
	if (!line)
		return (NULL);
	return (line);
}
/*
#include <stdio.h>
#include <fcntl.h>

int	main(void)
{
	int		fd;
	char	*line;

	fd = open("empty.txt", O_RDONLY);
	line = get_next_line(fd);
	while (line)
	{
		printf("%s|", line);
		free(line);
		line = get_next_line(fd);
	}
	printf("%s|", line);
	return (0);
}*/
