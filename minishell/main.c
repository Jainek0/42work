/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thcaquet <thcaquet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/18 18:43:03 by thcaquet          #+#    #+#             */
/*   Updated: 2025/05/01 15:25:47 by thcaquet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	g_status = 1;

int main(int ac, char **av, char **envp)
{
	t_data	data;

	data = set_data();
	(void)av;
	(void)envp;
	(void)ac;
	set_envs(&data, envp);
	mini_execve(&data, &av[1]);
	free_data(&data);
	return (0);
}