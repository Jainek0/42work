/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   short_check.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thcaquet <thcaquet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/17 09:19:57 by thcaquet          #+#    #+#             */
/*   Updated: 2025/07/02 16:35:07 by thcaquet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	check_id_exp(char c)
{
	return (ft_isalnum(c) || c == '_');
}

int	check_research(char *str, char *re)
{
	while (*str && *str == *re)
	{
		str++;
		re++;
	}
	return (*str && !*re && *str == '=');
}

int	check_print_env(char *str)
{
	while (*str && *str != '=')
		++str;
	if (*str == '=')
		return (1);
	return (0);
}

int	check_nam_export(char *str)
{
	while (*str && *str != '=')
	{
		if (!(ft_isalnum(*str) || *str == '_'))
			return (0);
		++str;
	}
	return (1);
}
