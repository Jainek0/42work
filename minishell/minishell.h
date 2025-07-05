/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thcaquet <thcaquet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/18 18:43:09 by thcaquet          #+#    #+#             */
/*   Updated: 2025/07/05 18:27:30 by thcaquet         ###   ########.fr       */
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
# include <sys/ioctl.h>
# include <sys/types.h>
# include <readline/readline.h>
# include <readline/history.h>
# include "libft/src/libft.h"

# define ERROR_ARGC "ERROR : NO ARGUMET VALID\n"
# define ERROR_MALLOC "ERROR : MALLOC FAILL\n"
# define ERROR_HEREDOC "ERROR : HEREDOC FAILL\n"
# define ERROR_GETWCD "ERROR : GETWCD\n"
# define ERROR_GETWCD "ERROR : GETWCD\n"

# define ERROR_EXECVE "ERROR : EXECVE\n"
# define ERROR_EXEC_PATH "No such file or directory\n"
# define ERROR_EXEC_CMD "Command not found\n"
# define ERROR_PERM "minishell: Permission denied\n"

# define ERROR_FILE_PERM "minishell: Permission denied\n"
# define ERROR_FILE_PATH "minishell: No such file or directory\n"

# define CD_TOO_MANY_ARG "minishell: cd: too many arguments\n"
# define CD_NO_DIRECTORY "minishell: cd: No such file or directory\n"
# define CD_NO_PERM "minishell: cd: Permission denied\n"
# define CD_HOME_NO_SET "minishell: cd: HOME not set\n"
# define CD_OLDPWD_NO_SET "minishell: cd: OLDPWD not set\n"
# define SIG_RED "minishell: warning: here-document at line 1 \
delimited by end-of-file\n"

# define MALLOC_FAILURE "ERROR : MALLOC FAILURE\n"
# define FORK_FAILURE "ERROR : FORK FAILURE\n"
# define OPEN_FAILURE "ERROR : OPEN FAILURE\n"
# define OPEN_GETWCD "ERROR : OPEN GETWCD\n"


# define EXPORT_NO_VALID "minishell: export: not a valid identifier\n"

# define EXIT_TOO_MANY_ARG "minishell: exit: too many arguments\n"
# define EXIT_NUMERIC_ARG "minishell: exit: numeric argument required\n"

# define INVALID_LINE "minishell: invalid line\n"
# define ERROR_ARG_MINISHELL "minishell: no argument please\n"

# define ARG 0
# define FONCTION 1
# define PIPE 2
# define INFILE 3
# define HEREDOC 4
# define OUTFILE 5
# define APPEND 6
# define REDINFILE 31
# define REDHEREDOC 41
# define REDOUTFILE 51
# define REDAPPEND 61

typedef struct s_envlist
{
	struct s_envlist	*next;
	char				*str;
}	t_envlist;

typedef struct s_fd
{
	char	*file;
	int		out;
	int		in;
}	t_fd;

typedef struct s_index
{
	int	i;
	int	w;
	int	m;
	int	h;
}	t_index;

typedef struct s_token
{
	struct s_token	*next;
	char			*str;
	int				type;
}	t_token;

typedef struct s_data
{
	t_envlist	*start;
	t_token		*first;
	char		**ltab;
	char		**sptr;
	char		**cmd;
	char		*line;
	char		*tmp;
	char		*ex;
	t_fd		std;
	t_fd		fd;
	int			len;
	int			pipe;
	int			error;
	pid_t		pid_fork;
	pid_t		*tab_pid_fork;
}	t_data;

void		mini_pwd(t_data *data, char **cmd);
void		mini_cd(t_data *data, char **cmd);
void		mini_echo(t_data *data, char **cmd);
void		mini_execve(t_data *data, char **cmd);
char		*mini_expand(t_data *data, char *str);
void		mini_export(t_data *data, char **cmd);
void		mini_pipe(t_data *data);
void		mini_exit(t_data *data, char **cmd);
void		mini_unset(t_data *data, char **cmd);

t_envlist	*lst_add_front(t_envlist *env, char *content);
void		lst_add_back(t_envlist *env, char *content);
void		lst_sort_str_tab(t_envlist **tab, int size);
int			lst_len(t_token *start);

t_envlist	*env_search(t_data *data, char *search);
char		*env_get_search(t_data *data, char *re);
char		*env_dup_search(t_data *data, char *re);
char		**env_w_search(t_data *data, char *re);
int			env_comp(char *str1, char *str2);

void		liberate_all(t_data *data, char *msg, int err);
char		*mini_readline(t_data *data, char *str);
void		mini_free_envlist(t_envlist *start);
t_token		*mini_free_toklist(t_token *first);
void		put_error(t_data *data, char *msg, int error);

char		**lst_to_tab(t_data *data);
void		free_data(t_data *data);
void		free_tab(char **tab);

void		set_envs(t_data *data, char **envp); //tmp
void		last_cmd(t_data *data, char *cmd, char **t_cmd);
void		env_unset(t_data *data, char *str);
void		mini_env(t_data *data);

t_data		set_data(void);
pid_t		set_fork(t_data *data);

int			red_truncate(t_data *data, char *file);
int			red_append(t_data *data, char *file);
int			red_read(t_data *data, char *file);
void		hook_heredoc(t_data *data, char *end);
void		red_heredoc(t_data *data, char *end);

int			check_research(char *str, char *re);
int			check_id_exp(char c);
int			check_print_env(char *str);
int			check_nam_export(char *str);

int			sig_check(t_data *data);
void		sig_reset(t_data *data);
void		sig_set(void);

char		**lst_token_to_tab(t_data *data);
int			is_alnum_tab(char **tab);

// ledupont

void		shell_invalid_line(t_data *data, char *msg);

void		free2dstr(char **strs);
void		ft_free(void **ptr);
void		shell_red_parse(t_data *data);
void		shell_fonction_parse(t_data *data);
void		shell_check_line(t_data *data, char *s, t_index *in);
void		shell_clean_line(t_data *data, t_token *cur, t_token *prev);
void		shell_clean_quote(char *str, int i);
int			shell_countwords(char *str);
int			shell_empty_expanding(t_data *data, char *s, int i, int l);
t_envlist	*shell_envlist_new(t_data *data, char **envp, int i);
int			shell_error_expanding(t_data *data, char *s, int i);
int			shell_exp_strcmp(char *envp, char *expand, int l);
int			shell_expand(t_data *data, char *s, int i);
int			shell_expand_nutcase(t_data *data, char *s, int i);
int			shell_expanding(t_data *data, char *cur, char *s, int i);
void		shell_free_envlist(t_envlist *start);
void		shell_free_token(t_token *first);
int			shell_isquote(char c);
int			shell_isredir(char *str, int i);
int			shell_isspace(char c);
void		shell_line_sep(t_data *data);
void		shell_line_set(t_data *data);
void		shell_manage_expand_redir(t_data *data, t_token *cur, t_token *prev);
void		shell_manage_expand_arg(t_data *data, t_token *cur, t_token *prev);
void		shell_mode_switch(char *str, t_index *in, int type);
int			shell_redircheck(char *str);
void		shell_redirection_switch(char **str, t_index *in, int i);
void		shell_sizeword(t_data *data);
void		shell_space_sep(t_data *data, char *str, t_index *in);
void		shell_spacing_sep(t_data *data, t_index *in, int type);
void		shell_split_line(t_data *data);
void		shell_to_clean(t_data *data);
int			shell_to_expand(t_data *data, char *s, int i);
int			shell_token_assign(char *str, int pt);
void		shell_token_cleaning(t_data *data);
t_token		*shell_token_new(t_data *data, char **strs, int i);
void		shell_tokenizer(t_data *data);

#endif
