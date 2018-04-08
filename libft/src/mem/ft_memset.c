/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abeauvoi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/11 18:43:39 by abeauvoi          #+#    #+#             */
/*   Updated: 2017/04/20 14:11:08 by abeauvoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>

void				*ft_memset(void *dst, int c, size_t n)
{
	unsigned char	*d;
	unsigned char	uc;

	if (n)
	{
		d = (unsigned char *)dst;
		uc = (unsigned char)c;
		while (n--)
			*d++ = uc;
	}
	return (dst);
}
