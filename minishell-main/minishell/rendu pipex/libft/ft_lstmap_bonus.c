/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ledupont <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/22 10:54:29 by ledupont          #+#    #+#             */
/*   Updated: 2024/10/22 10:54:34 by ledupont         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*new;
	t_list	*newhead;
	void	*ftmp;

	if (!lst || !del || !f)
		return (NULL);
	newhead = NULL;
	new = NULL;
	while (lst)
	{
		ftmp = f(lst->content);
		if (ftmp)
			new = ft_lstnew(ftmp);
		if (!new || ftmp == NULL)
		{
			del(ftmp);
			ft_lstclear(&newhead, del);
			return (NULL);
		}
		ft_lstadd_back(&newhead, new);
		lst = lst->next;
	}
	return (newhead);
}
