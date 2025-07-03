/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_unset.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thcaquet <thcaquet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/03 17:42:00 by thcaquet          #+#    #+#             */
/*   Updated: 2025/07/03 17:58:47 by thcaquet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	mini_unset(t_data *data, char **cmd)
{
	last_cmd(data, NULL, cmd);
	++cmd;
	while (*cmd)
	{
		env_unset(data, *cmd);
		++cmd;
	}
}
