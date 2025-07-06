/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_fork.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thcaquet <thcaquet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/01 15:15:42 by thcaquet          #+#    #+#             */
/*   Updated: 2025/07/06 07:10:30 by thcaquet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

pid_t	set_fork(t_data *data)
{
	pid_t	pid;

	pid = fork();
	data->pid_fork = pid;
	if (data->pid_fork == 0)
	{
		signal(SIGINT, SIG_DFL);
		signal(SIGQUIT, SIG_DFL);
	}
	if (data->pid_fork == -1)
	{
		if (data->p_new[0] > 0)
			close(data->p_new[0]);
		if (data->p_new[1] > 0)
			close(data->p_new[1]);
		if (data->p_old[0] > 0)
			close(data->p_old[0]);
		if (data->p_old[1] > 0)
			close(data->p_old[1]);
		liberate_all(data, FORK_FAILURE, 1);
	}
	return (pid);
}
