/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.h                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ledupont <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/30 12:24:40 by ledupont          #+#    #+#             */
/*   Updated: 2024/10/30 12:27:59 by ledupont         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_BONUS_H
# define GET_NEXT_LINE_BONUS_H
# include <unistd.h>
# include <stdlib.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 5
# endif

char	*gnl_bufjoin(char *line, char *buffer, int size);
void	gnl_bufset(char *buffer);
char	*gnl_crossroad(char *line, int fd, char *buffer, int jump);
int		gnl_endline(char *buffer);
char	*gnl_freeline(char *line);
char	*get_next_line(int fd);
char	*gnl_lineset(char *buffer, int jump);
char	*get_next_line(int fd);

#endif
