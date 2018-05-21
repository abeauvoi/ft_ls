/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abeauvoi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/02 06:09:11 by abeauvoi          #+#    #+#             */
/*   Updated: 2018/05/21 02:25:28 by abeauvoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "ft_ls.h"

static inline void	flush_buffer(t_ls *info, size_t len)
{
	ft_putstr(info->buf);
	ft_bzero(info->buf, len);
	info->a = info->buf;
}

inline void			strtobuf(t_ls *info, const char *str, int len)
{
	if (info->z - info->a < len)
		flush_buffer(info, info->a - info->buf);
	ft_memcpy(info->a, str, len);
	info->a += len;
}

inline void			chartobuf(t_ls *info, char c)
{
	if (info->a == info->z)
		flush_buffer(info, FT_LS_BUFSIZ);
	*(info->a++) = c;
}

char				*ft_ultoa(char *ptr, unsigned long val, bool is_negative)
{
	if (val < 10)
		*--ptr = TO_CHAR(val);
	else
	{
		while (val)
		{
			*--ptr = TO_CHAR(val % 10);
			val /= 10;
		}
	}
	if (is_negative)
		*--ptr = '-';
	return (ptr);
}

char				*pad_buffer(char *ptr, size_t len)
{
	while (len-- > 0)
		*ptr++ = ' ';
	return (ptr);
}
