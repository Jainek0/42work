/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_data.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thcaquet <thcaquet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/01 15:17:00 by thcaquet          #+#    #+#             */
/*   Updated: 2025/05/01 19:41:08 by thcaquet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_data	set_data(void)
{
	t_data data;

	data.end = NULL;
	data.start = NULL;
	data.line = NULL;
	data.error = 0;
	data.pipe = 0;
	data.std.in = dup(STDIN_FILENO);
	data.std.out = dup(STDOUT_FILENO);
	data.pid_fork = -2;
	data.fd.in = -2;
	data.fd.out = -2;
	return (data);
}