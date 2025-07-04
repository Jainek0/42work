/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sig.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thcaquet <thcaquet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/30 09:30:29 by thcaquet          #+#    #+#             */
/*   Updated: 2025/07/04 11:31:59 by thcaquet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	g_sig = 0;

int	sig_check(t_data *data)
{
	if (g_sig == 0)
		return (1);
	data->error = g_sig;
	return (0);
}

void	sig_reset(t_data *data)
{
	if (g_sig == 0)
		return ;
	data->error = g_sig;
	data->pipe = 0;
	g_sig = 0;
}

void	sig_ft(int sig)
{
	(void) sig;
	ioctl(1, TIOCSTI, "\n");
	rl_replace_line("", 0);
	rl_on_new_line();
	if (sig == SIGINT)
		g_sig = 130;
	else
		g_sig = 131;
}

void	sig_set(void)
{
	signal(SIGINT, &sig_ft);
	signal(SIGQUIT, &sig_ft);
}
