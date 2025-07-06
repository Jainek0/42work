/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_split_line.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thcaquet <thcaquet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/17 04:18:35 by ledupont          #+#    #+#             */
/*   Updated: 2025/07/06 04:39:54 by thcaquet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	shell_to_clean(t_data *data)
{
	t_token	*cur;

	cur = data->tok;
	data->prev = NULL;
	while (cur)
	{
		if (cur->type != HEREDOC)
			cur = shell_clean_line(data, cur);
		data->prev = cur;
		cur = cur->next;
	}
}

void	shell_split_line(t_data *data)
{
	t_index	in;

	ft_bzero(&in, sizeof(t_index));
	while (data->line[in.i])
	{
		if (in.m == 0 && shell_space(data->line[in.i]) == 0
			&& (in.i == 0 || (in.i && shell_space(data->line[in.i - 1]) == 1)))
			in.w++;
		shell_mode_switch(data->line, &in, 0);
		if (in.m != 0 || shell_space(data->line[in.i]) == 0)
		{
			data->strs[in.w - 1][in.h] = data->line[in.i];
			in.h++;
		}
		in.i++;
		if (in.m == 0 && ((shell_space(data->line[in.i]) == 1
					&& shell_space(data->line[in.i - 1]) == 0)
				|| (data->line[in.i] == 0
					&& shell_space(data->line[in.i - 1]) == 0)))
			in.h = 0;
	}
}

void	shell_sizeword(t_data *data)
{
	t_index	in;

	ft_bzero(&in, sizeof(t_index));
	while (data->line[in.i])
	{
		if (in.m == 0 && shell_space(data->line[in.i]) == 0
			&& (in.i == 0 || (in.i && shell_space(data->line[in.i - 1]) == 1)))
			in.w++;
		shell_mode_switch(data->line, &in, 0);
		if (in.m != 0 || shell_space(data->line[in.i]) == 0)
			in.h++;
		in.i++;
		if (in.m == 0 && ((shell_space(data->line[in.i]) == 1
					&& shell_space(data->line[in.i - 1]) == 0)
				|| (data->line[in.i] == 0
					&& shell_space(data->line[in.i - 1]) == 0)))
		{
			data->strs[in.w - 1] = ft_calloc(in.h + 1, sizeof(char));
			if (!data->strs[in.w - 1])
				liberate_all(data, ERROR_MALLOC, 1);
			in.h = 0;
		}
	}
}

int	shell_countwords(char *str)
{
	t_index	in;

	ft_bzero(&in, sizeof(t_index));
	while (str[in.i])
	{
		if (in.m == 0 && shell_space(str[in.i]) == 0
			&& (in.i == 0 || (in.i && shell_space(str[in.i - 1]) == 1)))
			in.w++;
		shell_mode_switch(str, &in, 0);
		in.i++;
	}
	return (in.w);
}

void	shell_line_sep(t_data *data)
{
	t_index	in;

	ft_bzero(&in, sizeof(t_index));
	while (data->line[in.i])
	{
		shell_space_sep(data, data->line, &in);
		shell_mode_switch(data->line, &in, 0);
		in.i++;
	}
	in.w = shell_countwords(data->line);
	data->strs = malloc(sizeof(char *) * (in.w + 1));
	if (!data->strs)
		liberate_all(data, ERROR_MALLOC, 1);
	in.i = -1;
	shell_sizeword(data);
	shell_split_line(data);
	data->strs[in.w] = NULL;
	ft_free((void **)&data->line);
	data->line = NULL;
	shell_tokenizer(data);
	free2dstr(&data->strs);
	shell_to_clean(data);
	shell_token_assign_bis(data);
}
