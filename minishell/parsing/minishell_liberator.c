/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_liberator.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thcaquet <thcaquet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/17 04:18:35 by ledupont          #+#    #+#             */
/*   Updated: 2025/07/04 16:32:03 by thcaquet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_free(void **ptr)
{
	free(*ptr);
	*ptr = NULL;
}

void	shell_invalid_line(char *str, char *msg)
{
	if (str && str != NULL)
		ft_free((void **)&str);
	if (msg)
		printf("Error : %s\n", msg);
}
