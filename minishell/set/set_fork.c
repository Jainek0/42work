/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_fork.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thcaquet <thcaquet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/01 15:15:42 by thcaquet          #+#    #+#             */
/*   Updated: 2025/07/05 16:36:59 by thcaquet         ###   ########.fr       */
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
		close(data->std.in);
		close(data->std.out);
		signal(SIGINT, SIG_DFL);
		signal(SIGQUIT, SIG_DFL);
	}
	if (data->pid_fork == -1)
		liberate_all(data, FORK_FAILURE, 1);
	return (pid);
}
