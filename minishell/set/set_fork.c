/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_fork.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thcaquet <thcaquet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/01 15:15:42 by thcaquet          #+#    #+#             */
/*   Updated: 2025/06/30 12:35:16 by thcaquet         ###   ########.fr       */
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
		mini_liberate_all(data, FORK_FAILURE, 1);
	return (pid);
}
