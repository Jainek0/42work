/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_split_line.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thcaquet <thcaquet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/17 04:18:35 by ledupont          #+#    #+#             */
/*   Updated: 2025/07/04 16:32:03 by thcaquet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	shell_to_clean(t_data *data)
{
	t_token	*cur;
	t_token	*prev;

	cur = data->first;
	prev = NULL;
	while (cur)
	{
		if (cur->type != HEREDOC)
			shell_clean_line(data, cur, prev);
		prev = cur;
		cur = cur->next;
	}
}

void	shell_split_line(t_data *data)
{
	t_index	in;

	ft_bzero(&in, sizeof(t_index));
	while (data->line[in.i])
	{
		if (in.m == 0 && shell_isspace(data->line[in.i]) == 0
			&& (in.i == 0 || (in.i && shell_isspace(data->line[in.i - 1]) == 1)))
			in.w++;
		shell_mode_switch(data->line, &in, 0);
		if (in.m != 0 || shell_isspace(data->line[in.i]) == 0)
		{
			data->ltab[in.w - 1][in.h] = data->line[in.i];
			in.h++;
		}
		in.i++;
		if (in.m == 0 && ((shell_isspace(data->line[in.i]) == 1
					&& shell_isspace(data->line[in.i - 1]) == 0)
				|| (data->line[in.i] == 0
					&& shell_isspace(data->line[in.i - 1]) == 0)))
			in.h = 0;
	}
}

void	shell_sizeword(t_data *data)
{
	t_index	in;

	ft_bzero(&in, sizeof(t_index));
	while (data->line[in.i])
	{
		if (in.m == 0 && shell_isspace(data->line[in.i]) == 0
			&& (in.i == 0 || (in.i && shell_isspace(data->line[in.i - 1]) == 1)))
			in.w++;
		shell_mode_switch(data->line, &in, 0);
		if (in.m != 0 || shell_isspace(data->line[in.i]) == 0)
			in.h++;
		in.i++;
		if (in.m == 0 && ((shell_isspace(data->line[in.i]) == 1
					&& shell_isspace(data->line[in.i - 1]) == 0)
				|| (data->line[in.i] == 0
					&& shell_isspace(data->line[in.i - 1]) == 0)))
		{
			data->ltab[in.w - 1] = ft_calloc(in.h + 1, sizeof(char));
			if (!data->ltab[in.w - 1])
				mini_liberate_all(data, "malloc failure", 1);
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
		if (in.m == 0 && shell_isspace(str[in.i]) == 0
			&& (in.i == 0 || (in.i && shell_isspace(str[in.i - 1]) == 1)))
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
	data->ltab = malloc(sizeof(char *) * (in.w + 1));
	if (!data->ltab)
		mini_liberate_all(data, "malloc failure", 1);
	in.i = -1;
	shell_sizeword(data);
	shell_split_line(data);
	data->ltab[in.w] = NULL;
	ft_free((void **)&data->line);
	data->line = NULL;
	shell_tokenizer(data);
	free2dstr(data->ltab);
	data->ltab = NULL;
	shell_to_clean(data);
}
