/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_token_expand.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thcaquet <thcaquet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/02 20:44:25 by ledupont          #+#    #+#             */
/*   Updated: 2025/07/03 13:27:34 by thcaquet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	shell_manage_expand_redir(t_data *data, t_token *cur, t_token *prev)
{
	(void)prev;
	if (ft_strlen(cur->str) == 0)
	{
		//shell_free_token(data->first);
		free(cur->str);
		cur->str = NULL;
		printf("minishell: $%s: ambiguous redirect\n", data->ex);
	}
}

void	shell_manage_expand_arg(t_data *data, t_token *cur, t_token *prev)
{
	if (ft_strlen(cur->str) == 0)
	{
		if (prev != NULL)
			prev->next = cur->next;
		else
			data->first = cur->next;
		free(cur->str);
		cur->str = NULL;
		free(cur);
		cur = NULL;
	}
}
