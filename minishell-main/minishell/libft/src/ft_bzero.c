/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bzero.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thcaquet <thcaquet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/08 14:50:29 by thcaquet          #+#    #+#             */
/*   Updated: 2024/10/11 17:15:17 by thcaquet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_bzero(void *s, size_t n)
{
	void	*witness;

	witness = s;
	while (n-- > 0)
	{
		*(unsigned char *) s = 0;
		s++;
	}
	return (witness);
}
