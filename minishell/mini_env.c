/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thcaquet <thcaquet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/21 19:24:09 by thcaquet          #+#    #+#             */
/*   Updated: 2025/04/29 08:57:57 by thcaquet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	mini_env(t_data *data)
{
	t_envlist	*env;

	env = data->start;
	while (env)
	{
		printf("%s\n", env->at);
		env = env->next;
	}
	data->error = 0;
}
