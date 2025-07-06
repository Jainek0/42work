/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_parsing.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thcaquet <thcaquet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/17 04:18:35 by ledupont          #+#    #+#             */
/*   Updated: 2025/07/06 06:58:41 by thcaquet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	shell_fonction_parse(t_data *data)
{
	if (!sig_check(data) || !data->tok)
		return ;
	data->cmd = lst_token_to_tab(data);
	if (data->tok->type == 1 && ft_strncmp(data->tok->str, "echo", 5) == 0)
		mini_echo(data, data->cmd);
	else if (data->tok->type == 1 && ft_strncmp(data->tok->str, "cd", 3) == 0)
		mini_cd(data, data->cmd);
	else if (data->tok->type == 1 && ft_strncmp(data->tok->str, "pwd", 4) == 0)
		mini_pwd(data, data->cmd);
	else if (data->tok->type == 1
		&& ft_strncmp(data->tok->str, "export", 7) == 0)
		mini_export(data, data->cmd);
	else if (data->tok->type == 1
		&& ft_strncmp(data->tok->str, "unset", 6) == 0)
		mini_unset(data, data->cmd);
	else if (data->tok->type == 1 && ft_strncmp(data->tok->str, "env", 4) == 0)
		mini_env(data);
	else if (data->tok->type == 1 && ft_strncmp(data->tok->str, "exit", 5) == 0)
		mini_exit(data, data->cmd);
	else if (data->tok->type == 1)
		mini_execve(data, data->cmd);
	free2dstr((char ***)&data->cmd);
}

t_token	*tok_unset(t_data *data, t_token *node)
{
	t_token	*lst;

	data->error = 0;
	lst = data->tok;
	if (!lst || !node)
		return (0);
	if (node == lst)
		lst = lst->next;
	else
	{
		while (lst->next != node)
			lst = lst->next;
		lst->next = node->next;
	}
	if (node == data->tok)
		data->tok = node->next;
	ft_free((void **)&node->str);
	ft_free((void **)&node);
	return (lst);
}

void	shell_red_parse(t_data *data)
{
	int		err[3];
	t_token	*node;

	node = data->tok;
	err[0] = 1;
	err[1] = 1;
	err[2] = 1;
	while (node && node->type != 2)
	{
		if (!sig_check(data))
			return ;
		if (err[0] == 1 && node->type == 3)
			err[0] = red_read(data, node->str);
		else if (node->type == 4)
			red_heredoc(data, node->str);
		else if (err[1] == 1 && node->type == 5)
			err[1] = red_truncate(data, node->str);
		else if (err[2] == 1 && node->type == 6)
			err[2] = red_append(data, node->str);
		if (node && node->type >= 3 && node->type <= 6)
			node = tok_unset(data, node);
		else
			node = node->next;
	}
}
