/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_exit.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thcaquet <thcaquet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/03 17:41:09 by thcaquet          #+#    #+#             */
/*   Updated: 2025/07/05 18:22:27 by thcaquet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	mini_exit(t_data *data, char **cmd)
{
	int	err;

	err = 0;
	printf("exit\n");
	if (cmd[1])
		data->error = (char) ft_atoll(cmd[1], &err);
	if (err == 2)
		put_error(data, EXIT_NUMERIC_ARG, 2);
	else if (ft_tab2len(cmd) > 2)
	{
		put_error(data, EXIT_TOO_MANY_ARG, 1);
		return ;
	}
	free2dstr(cmd);
	free_data(data);
	close(data->std.in);
	close(data->std.out);
	exit((char) data->error);
}
