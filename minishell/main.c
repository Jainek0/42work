/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thcaquet <thcaquet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/18 18:43:03 by thcaquet          #+#    #+#             */
/*   Updated: 2025/07/06 06:05:06 by thcaquet         ###   ########.fr       */
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
	free_data(data);
}

void	shell_error_token(t_data *data)
{
	if (data->pipe == AMBIGUOUS)
		put_error(data, AMBIGUOUS_ERROR, 2);
	else if (data->pipe == -1)
		put_error(data, UNEXPECTED"`newline'\n", 2);
	else if (data->pipe == -PIPE)
		put_error(data, UNEXPECTED"`|'\n", 2);
	else if (data->pipe == -REDINFILE)
		put_error(data, UNEXPECTED"`<'\n", 2);
	else if (data->pipe == -REDHEREDOC)
		put_error(data, UNEXPECTED"`<<'\n", 2);
	else if (data->pipe == -REDOUTFILE)
		put_error(data, UNEXPECTED"`>'\n", 2);
	else if (data->pipe == -REDAPPEND)
		put_error(data, UNEXPECTED"`>>'\n", 2);
}

void	main_hook(t_data *data)
{
	mini_history(data->line);
	shell_line_set(data);
	shell_error_token(data);
	if (data->tok && data->tok != NULL)
	{
		if (data->pipe == 0)
		{
			shell_red_parse(data);
			shell_fonction_parse(data);
		}
		else if (data->pipe > 0)
		{
			mini_pipe(data);
			data->tab_pid_fork = 0;
		}
	}
	data->tok = mini_free_toklist(&data->tok);
}

int	main(int argc, char **argv, char **envp)
{
	t_data	data;

	(void)argv;
	if (argc > 1)
	{
		ft_putstr_fd(ERROR_ARG_MINISHELL, 2);
		return (0);
	}
	data = set_data();
	set_envs(&data, envp);
	sig_set();
	while (1)
	{
		sig_reset(&data);
		data.line = mini_readline(&data, "minishell$ ");
		if (!data.line)
		{
			printf("exit\n");
			break ;
		}
		main_hook(&data);
	}
	main_end(&data);
	return (0);
}
