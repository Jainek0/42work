/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_echo.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thcaquet <thcaquet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/18 19:18:27 by thcaquet          #+#    #+#             */
/*   Updated: 2025/04/29 09:01:45 by thcaquet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	check_flag(char *str)
{
	int	r;

	r = 1;
	if (*str == '-')
		while (*(++str) == 'n')
			r = 0;
	if (*str)
		r = 1;
	return (r);
}

static void	echo_hook(char **cmd)
{
	int	flag;
	int	mod;

	flag = 0;
	mod = 0;
	while (*(++cmd))
	{
		if (check_flag(*cmd) + mod)
		{
			mod = 1;
			if (*(cmd + 1) && (check_flag(*(cmd + 1)) + mod))
				printf("%s ", *cmd);
			else
				printf("%s", *cmd);
		}
		else
			flag = 1;
	}
	if (!flag)
		printf("\n");
}

void	mini_echo(t_data data, char **cmd)
{
	if (!cmd)
	{
		printf("\n");
		return ;
	}
	echo_hook(cmd);
	data.error = 0;
}
