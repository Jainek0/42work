/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_pwd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thcaquet <thcaquet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/21 16:10:28 by thcaquet          #+#    #+#             */
/*   Updated: 2025/07/05 20:16:42 by thcaquet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	mini_pwd(t_data *data, char **cmd)
{
	char	*path;

	last_cmd(data, NULL, cmd);
	path = getcwd(0, 0);
	last_cmd(data, "pwd", NULL);
	if (path)
	{
		printf("%s\n", path);
		ft_free((void **)&path);
		data->error = 0;
	}
	else
		put_error(data, ERROR_GETWCD, 1);
}
