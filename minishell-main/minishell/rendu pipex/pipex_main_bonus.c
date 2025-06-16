/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_main.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ledupont <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 18:38:00 by ledupont          #+#    #+#             */
/*   Updated: 2025/02/18 20:05:36 by ledupont         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	main(int argc, char **argv, char **envp)
{
	t_tab	node;
	int		error;

	if (argc < 5 || !envp)
	{
		write(2, "not enough arguments\n", 21);
		return (0);
	}
	node.i = pipex_setpath(envp);
	if (node.i > -1)
	{
		node.path = ft_split(envp[node.i], ':');
		node.path[0] = pipex_cutpath(node.path[0], node.path);
	}
	else
		node.path = NULL;
	error = pipex_parsing(node, argc, argv, envp);
	return (error);
}
