/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abeauvoi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/11 19:34:45 by abeauvoi          #+#    #+#             */
/*   Updated: 2018/05/18 05:55:16 by abeauvoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static inline size_t	large_blocks_cpy(char **dst, const char **src,
		size_t len)
{
	long		*aligned_dst;
	const long	*aligned_src;

	aligned_dst = (long *)*dst;
	aligned_src = (const long *)*src;
	while (len >= BIG_BLOCK_SIZE)
	{
		*aligned_dst++ = *aligned_src++;
		*aligned_dst++ = *aligned_src++;
		*aligned_dst++ = *aligned_src++;
		*aligned_dst++ = *aligned_src++;
		len -= BIG_BLOCK_SIZE;
	}
	while (len >= LITTLE_BLOCK_SIZE)
	{
		*aligned_dst++ = *aligned_src++;
		len -= LITTLE_BLOCK_SIZE;
	}
	*dst = (char *)aligned_dst;
	*src = (const char *)aligned_src;
	return (len);
}

void					*ft_memcpy(void *dst0, const void *src0, size_t len)
{
	char		*dst;
	const char	*src;

	src = (const char *)src0;
	dst = (char *)dst0;
	if (!TOO_SMALL(len) && !UNALIGNED(src, dst))
		len = large_blocks_cpy(&dst, &src, len);
	while (len--)
		*dst++ = *src++;
	return (dst);
}
