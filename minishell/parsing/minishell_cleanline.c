/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_cleanline.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thcaquet <thcaquet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/17 04:18:35 by ledupont          #+#    #+#             */
/*   Updated: 2025/07/03 13:27:34 by thcaquet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	shell_redirection_switch(char **str, t_index *in, int i)
{
	if (in->m == 0 && i > 0 && shell_redircheck(str[i]) == 0
		&& ft_strncmp("<<", str[i - 1], 2) == 0)
		in->h = 1;
	else if (in->m == 0 && i == 0 && shell_redircheck(str[i]) == 1)
		in->h = -1;
	else if (in->m == 0 && shell_redircheck(str[i]) > 0
		&& (!str[i + 1] || str[i + 1] == NULL))
		in->h = -1;
	else
		in->h = 0;
}

void	shell_clean_quote(char *str, int i)
{
	int	l;

	l = ft_strlen(str);
	while (i < l)
	{
		str[i] = str[i + 1];
		i++;
	}
	str[i] = 0;
}

void	shell_mode_switch(char *str, t_index *in, int type)
{
	if (in->m == 0 && str[in->i] == '"')
	{
		if (type == 1 && in->h == 0)
			shell_clean_quote(str, in->i--);
		in->m = 2;
	}
	else if (in->m == 2 && str[in->i] == '"')
	{
		if (type == 1 && in->h == 0)
			shell_clean_quote(str, in->i--);
		in->m = 0;
	}
	else if (in->m == 0 && str[in->i] == '\'')
	{
		if (type == 1 && in->h == 0)
			shell_clean_quote(str, in->i--);
		in->m = 1;
	}
	else if (in->m == 1 && str[in->i] == '\'')
	{
		if (type == 1 && in->h == 0)
			shell_clean_quote(str, in->i--);
		in->m = 0;
	}
}

void	shell_clean_line(t_data *data, t_token *cur, t_token *prev)
{
	t_index	in;

	(void)prev;
	ft_bzero(&in, sizeof(t_index));
	data->sptr = &cur->str;
	while (cur && cur->str && cur->str != NULL && cur->str[in.i])
	{
		if (in.i >= 0 && in.m != 1 && cur->str
			&& cur->str[in.i] == '$'
			&& (ft_isalnum(cur->str[in.i + 1]) == 1
				|| cur->str[in.i + 1] == '?'
				|| cur->str[in.i + 1] == '_'))
			in.i = shell_expand(data, cur->str, in.i);
		if (cur->str[in.i])
		{
			shell_mode_switch(cur->str, &in, 1);
			in.i++;
		}
		if (data->ex)
		{
			free(data->ex);
			data->ex = NULL;
		}
	}
}
