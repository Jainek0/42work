/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thcaquet <thcaquet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/18 18:43:03 by thcaquet          #+#    #+#             */
/*   Updated: 2025/06/24 18:21:21 by thcaquet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	g_status = 1;

void	end_main(t_data *data)
{
	if (data->fd.in >= 0)
		close(data->fd.in);
	if (data->fd.out >= 0)
		close(data->fd.out);
	if (data->std.in >= 0)
		close(data->std.in);
	if (data->std.out >= 0)
		close(data->std.out);
}

int main(int ac, char **av, char **envp)
{
	t_data	data;
	//char *test[] = {"cat", "test=", "truc=", "a=1", NULL};

	data = set_data();
	(void)av;
	(void)envp;
	(void)ac;
	set_envs(&data, envp);
	mini_export(&data, av + 1);
	last_cmd(&data, "test");
	red_truncate(&data, "test");
	mini_env(&data);
	printf("\n================================\n\n");
	mini_export(&data, NULL);
	// red_heredoc(&data, "end");
	// red_read(&data, "test");
	// mini_echo(&data, av);
	// mini_execve(&data, &av[1]);
	free_data(&data);
	end_main(&data);
	return (0);
}
