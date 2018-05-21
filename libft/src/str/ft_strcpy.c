/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abeauvoi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/14 16:34:41 by abeauvoi          #+#    #+#             */
/*   Updated: 2018/05/20 22:16:54 by abeauvoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft_macros.h"

char		*ft_strcpy(char *dst0, const char *src0)
{
	const char	*src;
	char		*dst;
	const long	*aligned_src;
	long		*aligned_dst;

	src = src0;
	dst = dst0;
	if (!UNALIGNED(src, dst))
	{
		aligned_src = (const long *)src;
		aligned_dst = (long *)dst;
		while (!DETECT_NULL(*aligned_src))
			*aligned_dst++ = *aligned_src++;
		src = (const char *)aligned_src;
		dst = (char *)aligned_dst;
	}
	while ((*dst++ = *src++) != 0)
		continue ;
	return (dst0);
}
