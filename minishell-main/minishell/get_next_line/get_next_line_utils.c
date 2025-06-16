/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ledupont <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/30 12:22:49 by ledupont          #+#    #+#             */
/*   Updated: 2024/10/30 12:23:52 by ledupont         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int	gnl_endline(char *buffer)
{
	int		i;

	i = 0;
	while (i < BUFFER_SIZE)
	{
		i++;
		if (*buffer == '\n')
			return (i);
		if (*buffer == '\0')
			return (i - 1);
		buffer++;
	}
	return (-1);
}

char	*gnl_freeline(char *line)
{
	free(line);
	line = NULL;
	return (line);
}
