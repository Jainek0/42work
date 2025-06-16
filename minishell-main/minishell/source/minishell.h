/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leo <leo@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/06 20:07:19 by ledupont          #+#    #+#             */
/*   Updated: 2025/05/09 17:17:13 by leo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <string.h>
# include <fcntl.h>
# include <sys/wait.h>
# include <sys/types.h>
# include <readline/readline.h>
# include "../libft/libft.h"

# define INTMAX 2147483647
//# define INTMIN -2147483648
//# define NOERROR 0

typedef struct s_index
{
	int	i;
	int	w;
	int	m;
	int	h;
}	t_index;

typedef struct s_cmdlist
{
	char				*in;
	int					type;
	//struct t_envlist	*prev;
	struct s_cmdlist	*next;
}	t_cmdlist;

typedef struct s_envlist
{
	char				*at;
	//char				*in;
	//struct t_envlist	*prev;
	struct s_envlist	*next;
}	t_envlist;

typedef struct s_data
{
	struct s_envlist	*start;
	struct s_envlist	*end;
	//struct s_cmdlist	*first;
	char				**ltab;
	char				**sptr;
	char				*story;
	char				*line;
	char				*ex;
	char				*tmp;
	int					ind;
	int					len;
	int					error;
}	t_data;

void		free2dstr(char **strs);
void		ft_free(void *ptr);
void		mini_check_line(t_data *data, char *s, t_index *in);
void		mini_clean_line(t_data *data, int i);
void		mini_clean_quote(char *str, int i);
int			mini_countwords(char *str);
int			mini_empty_expanding(t_data *data, char *s, int i, int l);
t_envlist	*mini_envlist_new(t_data *data, char **envp, int i);
int			mini_error_expanding(t_data *data, char *s, int i);
int			mini_exp_strcmp(char *envp, char *expand, int l);
int			mini_expand(t_data *data, char *s, int i);
int			mini_expand_nutcase(t_data *data, char *s, int i);
int			mini_expanding(t_data *data, char *cur, char *s, int i);
void		mini_free_envlist(t_envlist *start);
void		mini_get_envp(t_data *data, char **envp);
int			mini_get_envp_check(char **envp, int i);
void		mini_invalid_line(char *str, char *msg);
int			mini_isquote(char c);
int			mini_isredir(char *str, int i);
int			mini_isspace(char c);
void		mini_liberate_all(t_data *data, char *msg, int err);
void		mini_line_sep(t_data *data);
void		mini_line_set(t_data *data);
void		mini_mode_switch(char *str, t_index *in, int type);
int			mini_redircheck(char *str);
void		mini_redirection_switch(char **str, t_index *in, int i);
void		mini_sizeword(t_data *data);
void		mini_space_sep(t_data *data, char *str, t_index *in);
void		mini_spacing_sep(t_data *data, t_index *in, int type);
void		mini_split_line(t_data *data);
int			mini_to_expand(t_data *data, char *s, int i);

#endif
