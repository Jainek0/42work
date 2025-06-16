/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_main_parsing.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leo <leo@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/17 04:18:35 by ledupont          #+#    #+#             */
/*   Updated: 2025/05/09 21:45:33 by leo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	mini_print_envp(t_data *data)
{
	t_envlist	*cur;

	if (data->start && data->start->at != NULL)
	{
		cur = data->start;
		while (cur != NULL)
		{
			printf("%s\n", cur->at);
			cur = cur->next;
		}
	}
}

int	main(int argc, char **argv, char **envp)
{
	t_data	data;
	int		i;

	(void)argv;
//	(void)argc;
	if (argc > 1)
	{
		write(2, "Error : no argument please\n", 27);
		return (0);
	}
	ft_bzero(&data, sizeof(t_data));
	mini_get_envp(&data, envp);
	while (1)
	{
		data.line = readline("ask > ");
		if (data.line && data.line != NULL)
			mini_line_set(&data);
		if (data.story && data.story != NULL)
			printf("story = %s\n", data.story);
		if (data.end && data.end->at != NULL)
			printf("und = %s\n", data.end->at);
		if (data.ltab)
		{
			i = 0;
			while (data.ltab && data.ltab[i])
				printf("%s\n", data.ltab[i++]);
			if (data.ltab && data.ltab[0]
				&& ft_strncmp(data.ltab[0], "exit", 5) == 0)
				mini_liberate_all(&data, NULL, 0);
			if (data.ltab && data.ltab[0]
				&& ft_strncmp(data.ltab[0], "env", 4) == 0)
				mini_print_envp(&data);
			free2dstr(data.ltab);
			data.ltab = NULL;
		}
	}
	return (0);
}
