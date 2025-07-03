/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_export.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thcaquet <thcaquet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/21 19:24:09 by thcaquet          #+#    #+#             */
/*   Updated: 2025/07/03 17:58:38 by thcaquet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	print_export(t_envlist **t_lst)
{
	int	i;
	int	j;

	j = -1;
	while (t_lst[++j])
	{
		i = 0;
		if (ft_strncmp(t_lst[j]->str, "_=", 2) == 0)
			continue ;
		while (t_lst[j]->str[i] && t_lst[j]->str[i] != '=')
			++i;
		if (t_lst[j]->str[i] == '=')
		{
			++i;
			printf("declare -x %.*s", i, t_lst[j]->str);
			if (t_lst[j]->str[i])
				printf("\"%s\"\n", &t_lst[j]->str[i]);
			else
				printf("\"\"\n");
		}
		else
			printf("declare -x %s\n", t_lst[j]->str);
	}
	free(t_lst);
}

void	export_print(t_data *data)
{
	t_envlist	*lst;
	t_envlist	**t_lst;
	int			i;
	int			j;

	last_cmd(data, "export", NULL);
	lst = data->start;
	i = 0;
	while (lst && ++i)
		lst = lst->next;
	t_lst = malloc(sizeof(t_envlist *) * (i + 1));
	if (!t_lst)
		mini_liberate_all(data, ERROR_MALLOC, 1);
	j = -1;
	lst = data->start;
	while (++j < i)
	{
		t_lst[j] = lst;
		lst = lst->next;
	}
	t_lst[j] = 0;
	lst_sort_str_tab(t_lst, i);
	print_export(t_lst);
}

void	mini_export(t_data *data, char **cmd)
{
	data->error = 0;
	last_cmd(data, NULL, cmd);
	++cmd;
	if (!*cmd)
		export_print(data);
	else
	{
		while (*cmd)
		{
			if (check_nam_export(*cmd))
				data->start = lst_add_front(data->start, *cmd);
			else
			{
				data->error = 1;
				printf("minishell: export: `%s': \
					not a valid identifier\n", *cmd);
			}
			++cmd;
		}
	}
}
