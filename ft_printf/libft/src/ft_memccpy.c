/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memccpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abeauvoi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/11 20:44:28 by abeauvoi          #+#    #+#             */
/*   Updated: 2017/04/17 20:20:18 by abeauvoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>

void					*ft_memccpy(void *dst, const void *src, int c, size_t n)
{
	unsigned char		*d;
	const unsigned char	*s;
	unsigned char		uc;

	s = (const unsigned char *)src;
	d = (unsigned char *)dst;
	uc = (unsigned char)c;
	while (n--)
		if ((*d++ = *s++) == uc)
			return (d);
	return (NULL);
}
