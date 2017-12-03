/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abeauvoi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/14 16:45:44 by abeauvoi          #+#    #+#             */
/*   Updated: 2017/04/18 18:20:40 by abeauvoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>

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
