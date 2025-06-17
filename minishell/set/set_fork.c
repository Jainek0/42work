/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_fork.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thcaquet <thcaquet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/01 15:15:42 by thcaquet          #+#    #+#             */
/*   Updated: 2025/06/17 11:23:32 by thcaquet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	set_fork(t_data *data)
{
	if (data->pid_fork <= -1)
	{
		data->pid_fork = fork();
		if (data->pid_fork == -1)
			mini_liberate_all(data, "Error : FORK", 1);
		if (data->pid_fork == 0)
		{
			signal(SIGINT, SIG_DFL);
			signal(SIGQUIT, SIG_DFL);
		}
	}
}
