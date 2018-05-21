/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abeauvoi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/14 16:45:44 by abeauvoi          #+#    #+#             */
/*   Updated: 2018/05/20 22:24:37 by abeauvoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft_types.h"

void					*ft_memchr(const void *s, int c, size_t n)
{
	const unsigned char *tmp;
	unsigned char		uc;

	tmp = (const unsigned char *)s;
	uc = (unsigned char)c;
	while (n--)
	{
		if (*tmp == uc)
			return ((void *)tmp);
		++tmp;
	}
	return (NULL);
}
