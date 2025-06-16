/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_parsing_is_checker.c                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leo <leo@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/17 04:18:35 by ledupont          #+#    #+#             */
/*   Updated: 2025/05/08 18:57:26 by leo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	mini_isspace(char c)
{
	if (c == ' ' || (c >= '\t' && c <= '\r'))
		return (1);
	return (0);
}

int	mini_isquote(char c)
{
	if (c == '"' || c == '\'')
		return (1);
	return (0);
}

int	mini_isredir(char *str, int i)
{
	if ((str[i] == '<' && str[i + 1] != '<')
		|| (str[i] == '>' && str[i + 1] != '<')
		|| str[i] == '|')
		return (1);
	return (0);
}

int	mini_redircheck(char *str)
{
	if (ft_strncmp("|", str, 2) == 0)
		return (1);
	if (ft_strncmp("<<", str, 2) == 0 || ft_strncmp("<", str, 2) == 0)
		return (2);
	if (ft_strncmp(">>", str, 2) == 0 || ft_strncmp(">", str, 2) == 0)
		return (3);
	return (0);
}
