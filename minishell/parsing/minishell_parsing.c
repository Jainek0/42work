/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_parsing.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thcaquet <thcaquet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/17 04:18:35 by ledupont          #+#    #+#             */
/*   Updated: 2025/07/04 00:52:36 by thcaquet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	shell_fonction_parse(t_data *data)
{
	char	**cmd;

	if (!sig_check(data))
		return ;
	cmd = lst_token_to_tab(data);
	if (data->first->type == FONCTION && ft_strncmp(data->first->str, "echo", 5) == 0)
		mini_echo(data, cmd);
	else if (data->first->type == FONCTION && ft_strncmp(data->first->str, "cd", 3) == 0)
		mini_cd(data, cmd);
	else if (data->first->type == FONCTION && ft_strncmp(data->first->str, "pwd", 4) == 0)
		mini_pwd(data, cmd);
	else if (data->first->type == FONCTION && ft_strncmp(data->first->str, "export", 7) == 0)
		mini_export(data, cmd);
	else if (data->first->type == FONCTION && ft_strncmp(data->first->str, "unset", 6) == 0)
		mini_unset(data, cmd);
	else if (data->first->type == FONCTION && ft_strncmp(data->first->str, "env", 4) == 0)
		mini_env(data);
	else if (data->first->type == FONCTION && ft_strncmp(data->first->str, "exit", 5) == 0)
		mini_exit(data, cmd);
	else if (data->first->type == FONCTION)
		mini_execve(data, cmd);
	free2dstr(cmd);
}

void	tok_unset(t_data *data, t_token *node)
{
	t_token	*lst;

	data->error = 0;
	lst = data->first;
	if (!lst)
		return ;
	if (!node)
		return ;
	if (node == data->first)
		data->first = data->first->next;
	else
	{
		while (lst->next != node)
			lst = lst->next;
		lst->next = node->next;
	}
	free(node->str);
	free(node);
}

void	shell_red_parse(t_data *data)
{
	t_token	*node;

	node = data->first;
	while (node && node->type != 2)
	{
		if (!sig_check(data))
			return ;
		if (data->first->type == REDINFILE)
		{
			tok_unset(data, node);
			red_read(data, node->str);
		}
		else if (data->first->type == REDHEREDOC)
			red_heredoc(data, node->str);
		else if (data->first->type == REDOUTFILE)
			red_truncate(data, node->str);
		else if (data->first->type == REDAPPEND)
			red_append(data, node->str);
		node = node->next;
	}
}
