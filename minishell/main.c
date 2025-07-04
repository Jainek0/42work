/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thcaquet <thcaquet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/18 18:43:03 by thcaquet          #+#    #+#             */
/*   Updated: 2025/07/04 19:48:01 by thcaquet         ###   ########.fr       */
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
	close(data->std.in);
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
		data.pipe = 0;
		sig_reset(&data);
		data.line = mini_readline(&data, "minishell :");
		if (!data.line)
		{
			break ;
			perror("exit\n");
		}
		mini_history(data.line);
		shell_line_set(&data);
		if (data.first && data.first != NULL)
		{
			if (data.pipe == 0)
			{
				shell_red_parse(&data);
				shell_fonction_parse(&data);
			}
			else if (data.pipe == -1)
				printf("minishell: syntax error near unexpected token 'newline' error: %d\n", data.error);
			else if (data.pipe < -1)
				printf("minishell: syntax error near unexpected token '%d' error: %d\n", data.pipe, data.error);
			else
			{
				mini_pipe(&data);
				free(data.tab_pid_fork);
				data.tab_pid_fork = 0;
			}
		}
		data.first = mini_free_toklist(data.first);
	}
	main_end(&data);
	return (0);
}
