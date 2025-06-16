/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   testarg.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ledupont <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/17 04:18:35 by ledupont          #+#    #+#             */
/*   Updated: 2025/04/17 04:18:38 by ledupont         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	mini_index_set(t_index *in)
{
	in->i = 0;
	in->w = 0;
	in->m = 0;
	in->h = 0;
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

int	mini_sec_strlen(char *str)
{
	int	i;

	i = 0;
	while (!str && str[i])
		i++;
	return (i);
}

void	mini_invalid_line(t_data *data)
{
	if (data->line && data->line != NULL)
	{
		free(data->line);
		data->line = NULL;
		printf("Error : invalid line\n");
	}
}

void	free2dstr(char **strs)
{
	int	i;

	i = -1;
	while (strs[++i])
		free(strs[i]);
	free(strs);
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
			free(clean->at);
		free(clean);
		clean = ntc;
	}
}

void	mini_liberate_all(t_data *data, char *msg, int err)
{
	if (data->tmp && data->tmp == NULL)
		free(data->tmp);
	if (data->start && data->start != NULL)
		mini_free_envlist(data->start);
	if (data->line && data->line != NULL)
		free(data->line);
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

int	mini_error_expanding(t_data *data, int i)
{
	char	*new;
	int		j;
	int		k;

	data->tmp = ft_itoa(data->error);
	if (!data->tmp)
		mini_liberate_all(data, "malloc failure", 1);
	new = malloc(sizeof(char) * (ft_strlen(data->line)
				+ ft_strlen(data->tmp) - 1));
	if (!new)
		mini_liberate_all(data, "malloc failure", 1);
	j = -1;
	while (++j < i)
		new[j] = data->line[j];
	k = 0;
	while (data->tmp[k])
		new[j++] = data->tmp[k++];
	k = i + 2;
	while (data->line[k])
		new[j++] = data->line[k++];
	new[j] = '\0';
	free(data->tmp);
	free(data->line);
	data->line = new;
	return (i - 1);
}

int	mini_empty_expanding(t_data *data, int i, int l)
{
	char	*new;
	int		j;
	int		n;

	n = ft_strlen(data->line) - l;
	new = malloc(sizeof(char) * (n + 1));
	if (!new)
		mini_liberate_all(data, "malloc failure", 1);
	j = -1;
	while (++j < i)
		new[j] = data->line[j];
	n = i + l;
	while (data->line[++n])
		new[j++] = data->line[n];
	new[j] = '\0';
	free(data->line);
	data->line = new;
	if (i > INTMAX)
	{
		mini_invalid_line(data);
		i = 0;
	}
	return (i - 1);
}

int	mini_expanding(t_data *data, char *cur, int i, int l)
{
	char	*new;
	int		j;
	int		n;

	n = ft_strlen(data->line) + ft_strlen(cur) - (l * 2);
	new = malloc(sizeof(char) * (n + 1));
	if (!new)
		mini_liberate_all(data, "malloc failure", 1);
	j = -1;
	while (++j < i)
		new[j] = data->line[j];
	n = i + l;
	while (cur[++l])
		new[j++] = cur[l];
	while (data->line[++n])
		new[j++] = data->line[n];
	new[j] = '\0';
	free(data->line);
	data->line = new;
	if (i > INTMAX)
	{
		mini_invalid_line(data);
		i = 0;
	}
	return (i);
}

int	mini_to_expand(t_data *data, int i, int l)
{
	t_envlist	*cur;

	cur = data->start;
	while (cur)
	{
		if (mini_exp_strcmp(cur->at, data->ex, l) == 0)
		{
			i = mini_expanding(data, cur->at, i, l);
			free(data->ex);
			return (i);
		}
		cur = cur->next;
	}
	i = mini_empty_expanding(data, i, l);
	free(data->ex);
	return (i);
}

int	mini_expand_nutcase(t_data *data, int i)
{
	if (data->line[i] == '?')
		return (mini_error_expanding(data, i - 1));
	if (data->line[i] >= '0' && data->line[i] <= '9')
		return (mini_empty_expanding(data, i - 1, 1));
	return (i);
}

int	mini_expand(t_data *data, int i)
{
	int		j;
	int		k;
	int		l;

	j = i + 1;
	if (data->line[j] == '?' || (data->line[j] >= '0' && data->line[j] <= '9'))
		return (mini_expand_nutcase(data, j));
	while (data->line[j] != ' ' && data->line[j] != 0 && data->line[j] != '$'
		&& data->line[j] != '>' && data->line[j] != '|' && data->line[j] != '<'
		&& !(data->line[j] >= '\t' && data->line[j] <= '\r')
		&& data->line[j] != '"' && data->line[j] != '\'')
		j++;
	l = j - i - 1;
	data->ex = malloc(sizeof(char) * (l + 1));
	if (!data->ex)
		mini_liberate_all(data, "malloc failure", 1);
	k = -1;
	j = i;
	while (++k < l)
		data->ex[k] = data->line[++j];
	data->ex[k] = '\0';
	i = mini_to_expand(data, i, l);
	return (i);
}

void	mini_redirection_switch(char *str, t_index *in)
{
	if (in->m == 0 && in->i > 0 && ((str[in->i] == '<'
				&& str[in->i - 1] == '<' && str[in->i + 1] == '<')
			|| (in->h == 0 && str[in->i] == '>'
				&& str[in->i - 1] == '>' && str[in->i + 1] == '>')))
		in->h = -1;
	if (in->m == 0 && in->i > 0 && in->h == 0 && str[in->i] == '<'
		&& str[in->i - 1] == '<')
		in->h = 1;
	if (in->m == 0 && in->h == 1 && ((str[in->i] == '<' || str[in->i] == '|'
				|| str[in->i] == '>') || (((str[in->i] >= '\t'
						&& str[in->i] <= '\r') || str[in->i] == ' ')
				&& !(str[in->i - 1] >= '\t' && str[in->i - 1] <= '\r')
				&& str[in->i - 1] != ' ' && str[in->i - 1] != '<'
				&& str[in->i - 2] != '<')))
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
	str[i] = '\0';
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

void	mini_clean_line(t_data *data)
{
	t_index	in;

	mini_index_set(&in);
	while (data->line != NULL && data->line[in.i])
	{
		if (in.i > INTMAX || (data->line[in.i] == '|'
				&& data->line[in.i + 1] == '|'))
			return (mini_invalid_line(data));
		mini_redirection_switch(data->line, &in);
		if (in.h == -1)
			return (mini_invalid_line(data));
		if (data->line && data->line[in.i] == '$' && in.m != 1 && in.h == 0
			&& data->line[in.i + 1] != ' ' && in.i >= 0
			&& data->line[in.i + 1] != 0 && data->line[in.i + 1] != '$'
			&& data->line[in.i + 1] != '"' && data->line[in.i + 1] != '\''
			&& !(data->line[in.i + 1] >= '\t' && data->line[in.i + 1] <= '\r'))
			in.i = mini_expand(data, in.i);
		mini_mode_switch(data->line, &in, 0);
		in.i++;
	}
	if (data->line != NULL && data->line && in.m != 0)
		mini_invalid_line(data);
}

char	**dupetab(char **src)
{
	char	**tab;
	int		i;

	i = 0;
	while (src[i])
		i++;
	tab = malloc(sizeof(char *) * (i + 1));
	if (!tab)
		return (NULL);
	i = -1;
	while (src[++i])
	{
		tab[i] = ft_strdup(src[i]);
		if (tab[i] == NULL)
		{
			free2dstr(tab);
			return (NULL);
		}
	}
	tab[i] = NULL;
	return (tab);
}

t_envlist	*mini_envlist_new(t_data *data, char **envp, int i)
{
	t_envlist	*new;

	new = malloc(sizeof(t_envlist));
	if (!new)
	{
		mini_liberate_all(data, "malloc failure", 1);
		exit (1);
	}
	new->at = ft_strdup(envp[i]);
	if (!new->at)
	{
		mini_liberate_all(data, "malloc failure", 1);
		exit (1);
	}
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
	}
	i = mini_get_envp_check(envp, i + 1);
	while (i != -1 && envp[i])
	{
		cur->next = mini_envlist_new(data, envp, i);
		cur = cur->next;
		i = mini_get_envp_check(envp, i + 1);
	}
	data->end = cur;
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

/*int	mini_countwords(char *str)
{
	t_index	in;

	mini_index_set(&in);
	while (str[++in.i])
	{
		mini_mode_switch(str, &in, 1);
		if (in.m != 0)
			in.w++;
		while (in.m != 0 && str[++in.i])
			mini_mode_switch(str, &in, 1);
		mini_redirection_switch(str, &in);
		if (str[in.i] && in.m == 0 && mini_isredir(str[in.i]) == 1)
			in.w++;
		else if (str[in.i] && in.m == 0 && in.i > 0
			&& mini_isspace(str[in.i]) == 1 && mini_isquote(str[in.i - 1]) == 0
			&& mini_isspace(str[in.i - 1]) == 0 && str[in.i - 1] != 0
			&& mini_isredir(str[in.i - 1]) == 0)
			in.w++;
	}
	if (in.i > 0 && mini_isspace(str[in.i - 1]) == 0
		&& mini_isquote(str[in.i - 1]) == 0 && mini_isredir(str[in.i - 1]) == 0)
		in.w++;
	return (in.w);
}*/

int	mini_countwords(char *str)
{
	t_index	in;

	mini_index_set(&in);
	while (str[++in.i])
	{
		if (str[in.i] && in.m == 0 && mini_isredir(str, in.i) == 1)
			in.w++;
		else if (str[in.i] && in.m == 0 && in.i > 0
			&& mini_isspace(str[in.i]) == 1 && mini_isquote(str[in.i - 1]) == 0
			&& mini_isspace(str[in.i - 1]) == 0 && str[in.i - 1] != 0
			&& mini_isredir(str, in.i - 1) == 0)
			in.w++;
		mini_mode_switch(str, &in, 0);
		while (in.m != 0 && str[in.i])
			mini_mode_switch(str, &in, 0);
		mini_redirection_switch(str, &in);
	}
	if (in.i > 0 && mini_isspace(str[in.i - 1]) == 0
		&& mini_isquote(str[in.i - 1]) == 0 && mini_isredir(str, in.i - 1) == 0)
		in.w++;
	return (in.w);
}

void	mini_line_split(t_data *data)
{
	int	w;
	//int	i;

	w = mini_countwords(data->line);
	printf("%d\n", w);
	/*data->ltab = malloc(sizeof(char *) * (w + 1));
	if (!data->ltab)
		mini_liberate_all(data, "malloc failure", 1);
	while (i < w)

	data->ltab[w] = NULL; *///
}

int	main(int argc, char **argv, char **envp)
{
	t_data	data;

	(void)argv;
//	(void)argc;
	if (argc > 1)
	{
		write(2, "Error\nno argument please\n", 25);
		return (0);
	}
	data.error = 0;
	mini_get_envp(&data, envp);
	while (1)
	{
		data.line = readline("ask > ");
		if (data.line)
		{
			mini_clean_line(&data);
			//if (data.line && data.line != NULL)
			//	mini_line_split(&data);
		}
		if (data.line && ft_strlen(data.line) && data.line[0] != '\0')
		{
			printf("%s\n", data.line);
			if (ft_strncmp(data.line, "exit", 4) == 0)
				mini_liberate_all(&data, NULL, 0);
			if (ft_strncmp(data.line, "env", 4) == 0)
				mini_print_envp(&data);
			free(data.line);
		}
	}
	return (0);
}
