/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abeauvoi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/14 17:52:48 by abeauvoi          #+#    #+#             */
/*   Updated: 2018/05/20 22:38:02 by abeauvoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft_macros.h"
#include "libft_types.h"

char		*ft_strncpy(char *dst0, const char *src0, size_t len)
{
	char		*dst;
	const long	*aligned_src;
	long		*aligned_dst;

	dst = dst0;
	if (!TOO_SMALL(len) && !UNALIGNED(src0, dst))
	{
		aligned_src = (const long *)src0;
		aligned_dst = (long *)dst0;
		while (len >= LITTLE_BLOCK_SIZE && !DETECT_NULL(*aligned_src))
		{
			len -= LITTLE_BLOCK_SIZE;
			*aligned_dst++ = *aligned_src++;
		}
	}
	while (len--)
	{
		*dst++ = *src0;
		if (*src0)
			++src0;
	}
	return (dst0);
}
