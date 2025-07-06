/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thcaquet <thcaquet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/28 16:20:16 by thcaquet          #+#    #+#             */
/*   Updated: 2025/07/06 05:14:12 by thcaquet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

size_t	lstlen_chr(t_envlist *node, char c)
{
	size_t	i;

	i = 0;
	while (node)
	{
		if (ft_strchr(node->str, c))
			i++;
		node = node->next;
	}
	return (i);
}

void	free_tab(char ***p_tab)
{
	char	**tab;
	int		i;

	i = 0;
	tab = *p_tab;
	while (tab[i])
		ft_free((void **)&tab[i++]);
	ft_free((void **)&tab);
	*p_tab = 0;
}

char	**lst_to_tab(t_data *data)
{
	int			i;
	char		**new;
	t_envlist	*node;

	i = 0;
	node = data->start;
	new = malloc(sizeof(char *) * (lstlen_chr(node, '=') + 1));
	if (!new)
		liberate_all(data, MALLOC_FAILURE, 1);
	while (node)
	{
		if (ft_strchr(node->str, '='))
		{
			new[i] = ft_strdup(node->str);
			if (!new[i])
			{
				free_tab((char ***)&new);
				liberate_all(data, MALLOC_FAILURE, 1);
			}
			i++;
		}
		node = node->next;
	}
	new[i] = 0;
	return (new);
}

void	put_error(t_data *data, char *msg, int error)
{
	ft_putstr_fd(msg, 2);
	data->error = error;
}

char	*mini_readline(t_data *data, char *str)
{
	char	*line;

	dup2(data->std.in, STDIN_FILENO);
	dup2(data->std.out, STDOUT_FILENO);
	line = readline(str);
	return (line);
}
