/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_split_space.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thcaquet <thcaquet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/04 23:01:02 by ledupont          #+#    #+#             */
/*   Updated: 2025/07/05 23:34:46 by thcaquet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	shell_count_str(char const *str)
{
	int	move;
	int	count;
	int	check_str;

	move = 0;
	count = 0;
	while (str[move])
	{
		check_str = 0;
		while (ft_strchr(" \t\n\v\f\r", str[move]) && str[move])
			move++;
		while (!ft_strchr(" \t\n\v\f\r", str[move]))
		{
			if (check_str == 0)
			{
				count++;
				check_str = 1;
			}
			move++;
		}
	}
	return (count);
}

char	*shell_catch_substring(char const *s, int begin, int ending)
{
	int		p;
	char	*substring;

	substring = malloc(sizeof(char) * (ending - begin + 1));
	if (!substring)
		return (NULL);
	p = -1;
	while (++begin <= ending)
		substring[++p] = s[begin - 1];
	substring[p + 1] = '\0';
	return (substring);
}

char	shell_addmanage(char **tab, const char *s,
	int *const istart, int j[1])
{
	if (*istart > *(istart + 1))
	{
		*(tab + ++*j) = shell_catch_substring(s, *(istart + 1), *istart);
		if (!*(tab + *j))
		{
			free2dstr(&tab);
			return (-1);
		}
	}
	return (0);
}

char	**shell_split_space(const char *s)
{
	int		i;
	int		j;
	int		start;
	char	**tab_substrings;

	i = 0;
	j = -1;
	tab_substrings = malloc(sizeof(char *) * (shell_count_str(s) + 1));
	if (!tab_substrings)
		return (NULL);
	while (s[i])
	{
		while (ft_strchr(" \t\n\v\f\r", s[i]) && s[i])
			i++;
		start = i;
		while (!ft_strchr(" \t\n\v\f\r", s[i]))
			i++;
		if (shell_addmanage(tab_substrings, s, (int [2]){i, start}, &j) < 0)
			return (NULL);
	}
	tab_substrings[j + 1] = NULL;
	return (tab_substrings);
}
