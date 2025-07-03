/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_bis.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thcaquet <thcaquet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/02 14:29:43 by thcaquet          #+#    #+#             */
/*   Updated: 2025/07/03 16:53:36 by thcaquet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	**lst_token_to_tab(t_data *data)
{
	t_token	*node;
	char	**cmd;
	int		len;
	int		i;

	len = lst_len(data->first);
	cmd = malloc((len + 1)* sizeof(char **));
	if (!cmd)
		mini_liberate_all(data, ERROR_MALLOC, 1);
	i = 0;
	node = data->first;
	while (node)
	{
		cmd[i] = ft_strdup(node->str);
		node = node->next;
		if (cmd[i] == 0)
			break ;
		++i;
	}
	cmd[i] = 0;
	return (cmd);
}

int	is_alnum_tab(char **tab)
{
	int	i;
	int	j;

	i = 0;
	while (tab[i])
	{
		j = 0;
		while((tab[i][j]))
		{
			if (!ft_isalnum(tab[i][j]) && !(j == 0 && tab[i][j] == '-'))
				return (1);
			++j;
		}
		++i;
	}
	return (0);
}
