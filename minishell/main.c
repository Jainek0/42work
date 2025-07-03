/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thcaquet <thcaquet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/18 18:43:03 by thcaquet          #+#    #+#             */
/*   Updated: 2025/07/04 00:48:48 by thcaquet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	mini_history(char *line)
{
	if (!line || ft_strcmp(line, "") == 0)
		return ;
	add_history(line);
}

void	main_end(t_data *data)
{
	if (data->fd.in >= 0)
		close(data->fd.in);
	if (data->fd.out >= 0)
		close(data->fd.out);
	if (data->std.in >= 0)
		close(data->std.in);
	if (data->std.out >= 0)
		close(data->std.out);
	free_data(data);
}

void	main_start(t_data *data, char **envp)
{
	*data = set_data();
	set_envs(data, envp);
	sig_set();
}

int	main(int argc, char **argv, char **envp)
{
	t_data	data;

	(void)argv;
	main_start(&data, envp);
	if (argc > 1)
	{
		write(2, ERROR_ARG_MINISHELL, 27);
		return (0);
	}
	while (1)
	{
		sig_reset(&data);
		data.line = readline("ask > ");
		mini_history(data.line);
		shell_line_set(&data);
		if (data.first && data.first != NULL)
		{
			shell_red_parse(&data);
			shell_fonction_parse(&data);
			if (ft_strncmp(data.first->str, "exit", 5) == 0)
			{
				mini_free_envlist(data.start);
				mini_free_toklist(data.first);
				exit (0);
			}
			else if (data.pipe == -1)
				printf("minishell: syntax error near unexpected token 'newline' error: %d\n", data.error);
			else if (data.pipe < -1)
				printf("minishell: syntax error near unexpected token '%d' error: %d\n", data.pipe, data.error);
			mini_free_toklist(data.first);
			data.first = NULL;
		}
		printf("piping 	:%d\n", data.pipe);
		printf("error	:%d\n", data.error);
	}
	main_end(&data);
	return (0);
}
