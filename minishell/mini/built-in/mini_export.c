/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_export.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thcaquet <thcaquet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/21 19:24:09 by thcaquet          #+#    #+#             */
/*   Updated: 2025/07/05 18:22:50 by thcaquet         ###   ########.fr       */
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
		liberate_all(data, ERROR_MALLOC, 1);
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

void	export_this(t_data *data, char *cmd, char *name)
{
	char	*content;
	char	**p_str;
	char	*str;

	content = env_get_search(data, name);
	str = cmd;
	while (str && *str && *str != '=')
		++str;
	if (!content || *str == '=')
	{
		p_str = env_w_search(data, name);
		*p_str = ft_strdup(cmd);
		if (!*p_str)
		{
			free(name);
			liberate_all(data, ERROR_MALLOC, 1);
		}
	}
}

void	export_check(t_data *data, char *cmd)
{
	char	*name;
	int		i;

	i = 0;
	while (cmd[i] && cmd[i] != '=')
		++i;
	name = ft_strndup(cmd, i);
	if (!name)
		liberate_all(data, ERROR_MALLOC, 1);
	if (env_search(data, name))
		export_this(data, cmd, name);
	else
		data->start = lst_add_front(data->start, cmd);
	free(name);
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
				export_check(data, *cmd);
			else
			{
				data->error = 1;
				put_error(data, EXPORT_NO_VALID, 1);
			}
			++cmd;
		}
	}
}
