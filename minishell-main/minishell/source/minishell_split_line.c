/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_split_line.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leo <leo@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/17 04:18:35 by ledupont          #+#    #+#             */
/*   Updated: 2025/05/09 21:58:59 by leo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	mini_split_line(t_data *data)
{
	t_index	in;

	ft_bzero(&in, sizeof(t_index));
	while (data->line[in.i])
	{
		if (in.m == 0 && mini_isspace(data->line[in.i]) == 0
			&& (in.i == 0 || (in.i && mini_isspace(data->line[in.i - 1]) == 1)))
			in.w++;
		mini_mode_switch(data->line, &in, 0);
		if (in.m != 0 || mini_isspace(data->line[in.i]) == 0)
		{
			data->ltab[in.w - 1][in.h] = data->line[in.i];
			in.h++;
		}
		in.i++;
		if (in.m == 0 && ((mini_isspace(data->line[in.i]) == 1
					&& mini_isspace(data->line[in.i - 1]) == 0)
				|| (data->line[in.i] == 0
					&& mini_isspace(data->line[in.i - 1]) == 0)))
			in.h = 0;
	}
}

void	mini_sizeword(t_data *data)
{
	t_index	in;

	ft_bzero(&in, sizeof(t_index));
	while (data->line[in.i])
	{
		if (in.m == 0 && mini_isspace(data->line[in.i]) == 0
			&& (in.i == 0 || (in.i && mini_isspace(data->line[in.i - 1]) == 1)))
			in.w++;
		mini_mode_switch(data->line, &in, 0);
		if (in.m != 0 || mini_isspace(data->line[in.i]) == 0)
			in.h++;
		in.i++;
		if (in.m == 0 && ((mini_isspace(data->line[in.i]) == 1
					&& mini_isspace(data->line[in.i - 1]) == 0)
				|| (data->line[in.i] == 0
					&& mini_isspace(data->line[in.i - 1]) == 0)))
		{
			data->ltab[in.w - 1] = ft_calloc(in.h + 1, sizeof(char));
			if (!data->ltab[in.w - 1])
				mini_liberate_all(data, "malloc failure", 1);
			in.h = 0;
		}
	}
}

int	mini_countwords(char *str)
{
	t_index	in;

	ft_bzero(&in, sizeof(t_index));
	while (str[in.i])
	{
		if (in.m == 0 && mini_isspace(str[in.i]) == 0
			&& (in.i == 0 || (in.i && mini_isspace(str[in.i - 1]) == 1)))
			in.w++;
		mini_mode_switch(str, &in, 0);
		in.i++;
	}
	return (in.w);
}

void	mini_line_sep(t_data *data)
{
	t_index	in;

	ft_bzero(&in, sizeof(t_index));
	while (data->line[in.i])
	{
		mini_space_sep(data, data->line, &in);
		mini_mode_switch(data->line, &in, 0);
		in.i++;
	}
	in.w = mini_countwords(data->line);
	data->ltab = malloc(sizeof(char *) * (in.w + 1));
	if (!data->ltab)
		mini_liberate_all(data, "malloc failure", 1);
	in.i = -1;
	mini_sizeword(data);
	mini_split_line(data);
	data->ltab[in.w] = NULL;
	ft_free(data->line);
	data->line = NULL;
	in.i = -1;
	while (data->ltab && data->ltab[++in.i])
		mini_clean_line(data, in.i);
}
