/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thcaquet <thcaquet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/18 18:43:03 by thcaquet          #+#    #+#             */
/*   Updated: 2025/07/02 20:02:53 by thcaquet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	end_main(t_data *data)
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

t_token *new_token(const char *str, int type)
{
	t_token *node = malloc(sizeof(t_token));
	if (!node)
		return NULL;
	node->str = strdup(str);
	node->type = type;
	node->next = NULL;
	return node;
}

t_token *create_token_list(char *args[], int size)
{
	t_token *head = NULL;
	t_token *current = NULL;
	int i = 0;

	while (i < size)
	{
		t_token *new = new_token(args[i], (i % 2 == 1) ? 2 : 0);
		if (!head)
			head = new;
		else
			current->next = new;
		current = new;
		i++;
	}
	return head;
}

void print_tokens(t_token *lst)
{
	while (lst)
	{
		printf("%s -> %d\n", lst->str, lst->type);
		lst = lst->next;
	}
}

int main(int ac, char **av, char **envp)
{
	t_data	data;
	char	*test[] = {"cd", "test", "0", 0};
	
	data = set_data();
	// data.test[0] = "sleep";
	// data.test[1] = "5";
	// data.test[2] = 0;
	(void)av;
	(void)envp;
	(void)ac;
	sig_set();
	set_envs(&data, envp);

	printf("_ = %s\n", env_get_search(&data, "_"));
	mini_echo(&data, test);
	printf("_ = %s\n", env_get_search(&data, "_"));

	// char *args[] = {"sleep", "|", "sleep", "|", "sleep", "|", "sleep"};
	// data.first = create_token_list(args, 7);
	end_main(&data);
	return (0);
}
