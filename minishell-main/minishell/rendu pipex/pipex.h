/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ledupont <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 20:05:53 by ledupont          #+#    #+#             */
/*   Updated: 2025/02/18 20:06:27 by ledupont         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <string.h>
# include <fcntl.h>
# include <sys/wait.h>
# include <sys/types.h>
# include "libft/libft.h"

# define FD_READ 0
# define FD_WRITE 1

typedef struct s_tab
{
	int		i;
	int		in;
	int		out;
	pid_t	pid;
	pid_t	lastpid;
	pid_t	pidtab[1024];
	int		errortab[1024];
	int		error;
	int		lasterror;
	int		wstatus;
	int		pipefd[2];
	char	**path;
	char	**cmd;
	char	*cmdpath;
}	t_tab;

char	*pipex_cmdcheck(char **cmd, char **path);
char	*pipex_cmdpath(char *cmd, char *path);
char	*pipex_cutpath(char *str, char **path);
void	pipex_execute_cmd(t_tab node, char **argv, char **envp);
int		pipex_fdcheck(char *argv, int type);
int		pipex_fork_process(t_tab node, char **argv, char **envp);
void	pipex_free_all(char **path, char **cmd, char *cmdpath, int error);
int		pipex_parsing(t_tab node, int argc, char **argv, char **envp);
int		pipex_setpath(char **envp);

#endif
