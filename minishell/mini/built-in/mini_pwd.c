/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_pwd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thcaquet <thcaquet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/21 16:10:28 by thcaquet          #+#    #+#             */
/*   Updated: 2025/07/02 20:30:05 by thcaquet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	mini_pwd(t_data *data)
{
	char	*path;

	path = getcwd(0, 0);
	last_cmd(data, "pwd", NULL);
	if (*path)
	{
		printf("%s\n", path);
		free(path);
		data->error = 0;
	}
	else
	{
		ft_putstr_fd(ERROR_GETWCD, 2);
		data->error = 1;
	}
}
