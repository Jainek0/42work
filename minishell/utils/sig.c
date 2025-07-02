/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sig.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thcaquet <thcaquet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/30 09:30:29 by thcaquet          #+#    #+#             */
/*   Updated: 2025/07/02 16:37:32 by thcaquet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	g_sig = 1;

int	sig_check(t_data *data)
{
	if (g_sig)
		return (1);
	data->error = 130;
	return (0);
}

void	sig_ft(int sig)
{
	(void) sig;
	ioctl(1, TIOCSTI, "\n");
	rl_replace_line("", 0);
	rl_on_new_line();
	g_sig = 0;
}

void	sig_set(void)
{
	signal(SIGINT, &sig_ft);
	signal(SIGQUIT, SIG_IGN);
}
