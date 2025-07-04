/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_exit.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thcaquet <thcaquet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/03 17:41:09 by thcaquet          #+#    #+#             */
/*   Updated: 2025/07/04 15:40:09 by thcaquet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	mini_exit(t_data *data, char **cmd)
{
	free_data(data);
	if (is_alnum_tab(cmd))
	{
		printf("%s\n", EXIT_NUMERIC_ARG);
		free2dstr(cmd);
		exit(data->error);
	}
	if (ft_tab2len(cmd) > 2)
	{
		printf("%s\n", EXIT_TOO_MANY_ARG);
		free2dstr(cmd);
		exit(data->error);
	}
	if (cmd[1])
		data->error = (char) ft_atoi(cmd[1]);
	free2dstr(cmd);
	close(data->std.in);
	close(data->std.out);
	exit((char) data->error);
}
