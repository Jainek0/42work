/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   testargv0.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leo <leo@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/17 04:18:35 by ledupont          #+#    #+#             */
/*   Updated: 2025/05/08 19:13:39 by leo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_free(void *ptr)
{
	free(ptr);
	ptr = NULL;
}

int	mini_isspace(char c)
{
	if (c == ' ' || (c >= '\t' && c <= '\r'))
		return (1);
	return (0);
}

int	mini_isquote(char c)
{
	if (c == '"' || c == '\'')
		return (1);
	return (0);
}

int	mini_isredir(char *str, int i)
{
	if ((str[i] == '<' && str[i + 1] != '<')
		|| (str[i] == '>' && str[i + 1] != '<')
		|| str[i] == '|')
		return (1);
	return (0);
}

void	mini_invalid_line(char *str, char *msg)
{
	if (str && str != NULL)
	{
		free(str);
		str = NULL;
	}
	if (msg)
		printf("Error : %s\n", msg);
}

void	free2dstr(char **strs)
{
	int	i;

	i = 0;
	while (strs && strs[i] != NULL)
	{
		free(strs[i]);
		strs[i] = NULL;
		i++;
	}
	free(strs);
	strs = NULL;
}

void	mini_free_envlist(t_envlist *start)
{
	t_envlist	*clean;
	t_envlist	*ntc;

	clean = start;
	while (clean)
	{
		ntc = clean->next;
		if (clean->at)
		{
			ft_free(clean->at);
			clean->at = NULL;
		}
		free(clean);
		clean = NULL;
		clean = ntc;
	}
	clean = NULL;
}

void	mini_liberate_all(t_data *data, char *msg, int err)
{
	if (data->ltab && data->ltab != NULL)
		free2dstr(data->ltab);
	if (data->story && data->story != NULL)
		ft_free(data->story);
	if (data->tmp && data->tmp != NULL)
		ft_free(data->tmp);
	if (data->start && data->start != NULL)
		mini_free_envlist(data->start);
	if (data->line && data->line != NULL)
		ft_free(data->line);
	if (err > 0)
		printf("Error : ");
	if (msg != NULL)
		printf("%s\n", msg);
	exit (err);
}

int	mini_exp_strcmp(char *envp, char *expand, int l)
{
	int	i;

	i = 0;
	while (envp[i] && expand[i])
	{
		if (envp[i] != expand[i])
			return (1);
		if (envp[i + 1] == '=' && i == l - 1)
			return (0);
		i++;
	}
	return (1);
}

int	mini_error_expanding(t_data *data, char *s, int i)
{
	char	*new;
	int		j;
	int		k;

	data->tmp = ft_itoa(data->error);
	if (!data->tmp)
		mini_liberate_all(data, "malloc failure", 1);
	new = malloc(sizeof(char) * (ft_strlen(s)
				+ ft_strlen(data->tmp) - 1));
	if (!new)
		mini_liberate_all(data, "malloc failure", 1);
	j = -1;
	while (++j < i)
		new[j] = s[j];
	k = 0;
	while (data->tmp[k])
		new[j++] = data->tmp[k++];
	k = i + 2;
	while (s[k])
		new[j++] = s[k++];
	new[j] = '\0';
	ft_free(data->tmp);
	free(s);
	*data->sptr = new;
	return (i - 1);
}

int	mini_empty_expanding(t_data *data, char *s, int i, int l)
{
	char	*new;
	int		j;
	int		n;

	n = ft_strlen(s) - l;
	new = malloc(sizeof(char) * (n + 1));
	if (!new)
		mini_liberate_all(data, "malloc failure", 1);
	j = -1;
	while (++j < i)
		new[j] = s[j];
	n = i + l;
	while (s[++n])
		new[j++] = s[n];
	new[j] = '\0';
	free(s);
	*data->sptr = new;
	return (i - 1);
}

int	mini_expanding(t_data *data, char *cur, char *s, int i)
{
	char	*new;
	int		j;
	int		n;

	n = ft_strlen(s) + ft_strlen(cur) - (data->len * 2);
	new = malloc(sizeof(char) * (n + 1) + 1);
	if (!new)
		mini_liberate_all(data, "malloc failure", 1);
	j = -1;
	while (++j < i)
		new[j] = s[j];
	n = i + data->len;
	while (cur[++data->len])
		new[j++] = cur[data->len];
	i = j - 1;
	while (s[++n])
		new[j++] = s[n];
	new[j] = '\0';
	free(s);
	*data->sptr = new;
	return (i);
}

/*int	mini_expanding(t_data *data, char *cur, char **s, int i)
{
	char	*new;
	//int		j;
	int		n;

	n = ft_strlen(*s) + ft_strlen(cur) - (data->len * 2);
	new = malloc(sizeof(char) * (n + 1) + 1);
	if (!new)
		mini_liberate_all(data, "malloc failure", 1);
	//j = -1;
	//while (++j < i)
	//	new[j] = *s[j];
	printf("str: %s\n", *s);
	printf("cur: %s\n", cur);
	printf("i: %d\n", i);
	printf("len: %d\n", data->len);
	
	ft_memcpy(new, *s, i);
	new[i] = '\0';

	printf("cp1: %s\n", new);

	strcat(new, cur + data->len + 1);
	printf("cp2: %s\n", new);
	strcat(new, *s + i + data->len + 1);
	
	printf("cp3: %s\n", new);
	//n = i + data->len;
	//while (cur[++data->len])
	//	new[j++] = cur[data->len];

	//while (*s[++n])
	//	new[j++] = *s[n];

	// strjoin 
	//new[j] = '\0';
	free(*s);
	*s = new;
	printf("%s\n", *s);
	if (i > INTMAX)
	{
		mini_invalid_line(*s);
		i = 0;
	}
	return (i);
}*/

int	mini_to_expand(t_data *data, char *s, int i)
{
	t_envlist	*cur;

	cur = data->start;
	while (cur)
	{
		if (mini_exp_strcmp(cur->at, data->ex, data->len) == 0)
		{
			free(data->ex);
			i = mini_expanding(data, cur->at, s, i);
			return (i);
		}
		cur = cur->next;
	}
	free(data->ex);
	i = mini_empty_expanding(data, s, i, data->len);
	return (i);
}

int	mini_expand_nutcase(t_data *data, char *s, int i)
{
	if (s[i] == '?')
		return (mini_error_expanding(data, s, i - 1));
	if (s[i] >= '0' && s[i] <= '9')
		return (mini_empty_expanding(data, s, i - 1, 1));
	return (i);
}

int	mini_expand(t_data *data, char *s, int i)
{
	int		j;
	int		k;

	j = i + 1;
	if (s[j] == '?' || (s[j] >= '0' && s[j] <= '9'))
		return (mini_expand_nutcase(data, s, j));
	while (ft_isalnum(s[j]) == 1 || s[j] == '_')
		j++;
	data->len = j - i - 1;
	data->ex = malloc(sizeof(char) * (data->len + 1));
	if (!data->ex)
		mini_liberate_all(data, "malloc failure", 1);
	k = -1;
	j = i;
	while (++k < data->len)
		data->ex[k] = s[++j];
	data->ex[k] = '\0';
	i = mini_to_expand(data, s, i);
	return (i);
}

int	mini_redircheck(char *str)
{
	if (ft_strncmp("|", str, 2) == 0)
		return (1);
	if (ft_strncmp("<<", str, 2) == 0 || ft_strncmp("<", str, 2) == 0)
		return (2);
	if (ft_strncmp(">>", str, 2) == 0 || ft_strncmp(">", str, 2) == 0)
		return (3);
	return (0);
}

void	mini_redirection_switch(char **str, t_index *in, int i)
{
	if (in->m == 0 && i > 0 && mini_redircheck(str[i]) == 0
		&& ft_strncmp("<<", str[i - 1], 2) == 0)
		in->h = 1;
	else if (in->m == 0 && i == 0 && mini_redircheck(str[i]) == 1)
		in->h = -1;
	else if (in->m == 0 && mini_redircheck(str[i]) > 0
		&& (!str[i + 1] || str[i + 1] == NULL))
		in->h = -1;
	else
		in->h = 0;
}

void	mini_clean_quote(char *str, int i)
{
	int	l;

	l = ft_strlen(str);
	while (i < l)
	{
		str[i] = str[i + 1];
		i++;
	}
	str[i] = 0;
}

void	mini_mode_switch(char *str, t_index *in, int type)
{
	if (in->m == 0 && str[in->i] == '"')
	{
		if (type == 1 && in->h == 0)
			mini_clean_quote(str, in->i--);
		in->m = 2;
	}
	else if (in->m == 2 && str[in->i] == '"')
	{
		if (type == 1 && in->h == 0)
			mini_clean_quote(str, in->i--);
		in->m = 0;
	}
	else if (in->m == 0 && str[in->i] == '\'')
	{
		if (type == 1 && in->h == 0)
			mini_clean_quote(str, in->i--);
		in->m = 1;
	}
	else if (in->m == 1 && str[in->i] == '\'')
	{
		if (type == 1 && in->h == 0)
			mini_clean_quote(str, in->i--);
		in->m = 0;
	}
}

void	mini_spacing_sep(t_data *data, t_index *in, int type)
{
	int		i;
	int		j;
	char	*new;

	new = malloc(sizeof(char) * (ft_strlen(data->line) + 3));
	if (!new)
		mini_liberate_all(data, "malloc failure", 1);
	j = -1;
	while (++j < in->i)
		new[j] = data->line[j];
	new[j++] = ' ';
	i = in->i;
	new[j++] = data->line[i++];
	if (type == 1)
		new[j++] = data->line[i++];
	new[j++] = ' ';
	while (data->line[i])
		new[j++] = data->line[i++];
	new[j] = '\0';
	free(data->line);
	data->line = new;
	in->i = in->i + type + 1;
}

void	mini_space_sep(t_data *data, char *str, t_index *in)
{
	if (in->m == 0 && ((str[in->i] == '<' && str[in->i + 1] != '<')
			|| (str[in->i] == '>' && str[in->i + 1] != '>')
			|| str[in->i] == '|'))
		mini_spacing_sep(data, in, 0);
	else if (in->m == 0 && ((str[in->i] == '<' && str[in->i + 1] == '<')
			|| (str[in->i] == '>' && str[in->i + 1] == '>')))
		mini_spacing_sep(data, in, 1);
}

void	mini_clean_line(t_data *data, int i)
{
	t_index	in;

	ft_bzero(&in, sizeof(t_index));
	data->sptr = &data->ltab[i];
	data->ind = i;
	mini_redirection_switch(data->ltab, &in, i);
	while (data->ltab[i] && data->ltab[i] != NULL && data->ltab[i][in.i])
	{
		if (in.i >= 0 && in.m != 1 && in.h == 0 && data->ltab[i]
			&& data->ltab[i][in.i] == '$'
			&& (ft_isalnum(data->ltab[i][in.i + 1]) == 1
			|| data->ltab[i][in.i + 1] == '?'
			|| data->ltab[i][in.i + 1] == '_'))
		{
			in.i = mini_expand(data, data->ltab[i], in.i);
			//cur->type = 1;
		}
		mini_mode_switch(data->ltab[i], &in, 1);
		// if (in.m != 0)
			// cur->type = 1;
		in.i++;
	}
}

t_envlist	*mini_envlist_new(t_data *data, char **envp, int i)
{
	t_envlist	*new;

	new = malloc(sizeof(t_envlist));
	if (!new)
		mini_liberate_all(data, "malloc failure", 1);
	new->at = ft_strdup(envp[i]);
	if (!new->at)
		mini_liberate_all(data, "malloc failure", 1);
	new->next = NULL;
	return (new);
}

int	mini_get_envp_check(char **envp, int i)
{
	int	j;

	while (envp[i])
	{
		j = -1;
		while (envp[i][++j])
			if (envp[i][j] == '=')
				return (i);
		i++;
	}
	return (-1);
}

void	mini_get_envp(t_data *data, char **envp)
{
	int			i;
	t_envlist	*cur;

	cur = NULL;
	data->start = NULL;
	i = mini_get_envp_check(envp, 0);
	if (i == -1)
		return ;
	if (envp[i])
	{
		data->start = mini_envlist_new(data, envp, i);
		cur = data->start;
		if (ft_strncmp(cur->at, "_=", 2) == 0)
			data->und = cur;
	}
	i = mini_get_envp_check(envp, i + 1);
	while (i != -1 && envp[i])
	{
		if (ft_strncmp(cur->at, "_=", 2) == 0)
			data->und = cur;
		cur->next = mini_envlist_new(data, envp, i);
		cur = cur->next;
		i = mini_get_envp_check(envp, i + 1);
	}
}

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
	free(data->line);
	data->line = NULL;
	in.i = -1;
	while (data->ltab && data->ltab[++in.i])
		mini_clean_line(data, in.i);
}

void	mini_check_line(t_data *data, char *s, t_index *in)
{
	if (in->m == 0
		&& (s[in->i] == '|' && s[in->i + 1] == '|'))
	{
		free(data->line);
		data->line = NULL;
	}
	else if (in->m == 0 && s[in->i + 1] != 0
		&& ((s[in->i] == '<' && s[in->i + 1] == '<' && s[in->i + 2] == '<')
			|| (s[in->i] == '>' && s[in->i + 1] == '>' && s[in->i + 2] == '>')))
	{
		free(data->line);
		data->line = NULL;
	}
}

void	mini_line_set(t_data *data)
{
	t_index	in;

	ft_bzero(&in, sizeof(t_index));
	if (!data->line)
		return ;
	while (data->line != NULL
		&& (mini_isspace(data->line[in.i]) == 1 || data->line[in.i] == 0))
		if (data->line[in.i++] == 0)
			return (mini_invalid_line(data->line, NULL));
	if (data->story)
		free(data->story);
	data->story = ft_strdup(data->line);
	if (!data->story)
		mini_liberate_all(data, "malloc failure", 1);
	in.i = -1;
	while (data->line && data->line[++in.i])
	{
		mini_mode_switch(data->line, &in, 0);
		mini_check_line(data, data->line, &in);
	}
	if (data->line && data->line != NULL && in.m == 0)
		mini_line_sep(data);
	else
		mini_invalid_line(data->line, "invalid line");
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
		{
			printf("story = %s\n", data.story);
			printf("und = %s\n", data.und->at);
		}
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
