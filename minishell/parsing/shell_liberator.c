/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_liberator.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thcaquet <thcaquet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/17 04:18:35 by ledupont          #+#    #+#             */
/*   Updated: 2025/07/05 23:33:08 by thcaquet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_free(void **ptr)
{
	free(*ptr);
	*ptr = NULL;
}

void	shell_invalid_line(t_data *data, char *msg)
{
	if (data->line && data->line != NULL)
		ft_free((void **)&data->line);
	if (msg)
		put_error(data, msg, 2);
}
