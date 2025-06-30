/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sig.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thcaquet <thcaquet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/30 09:30:29 by thcaquet          #+#    #+#             */
/*   Updated: 2025/06/30 16:11:58 by thcaquet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int		get_set_global(int nb)
{
	int static status = 0;
}

void	sa_sig(int sig)
{
	if (sig == SIGINT)
		printf("end ?\n");
	ioctl(1, TIOCSTI, "\n");
}

void	set_sig()
{
	signal(SIGINT, &sa_sig);
	signal(SIGQUIT, SIG_IGN);
}