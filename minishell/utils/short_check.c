/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   short_check.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thcaquet <thcaquet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/17 09:19:57 by thcaquet          #+#    #+#             */
/*   Updated: 2025/06/17 09:38:11 by thcaquet         ###   ########.fr       */
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