/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abeauvoi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/02 06:09:11 by abeauvoi          #+#    #+#             */
/*   Updated: 2018/05/02 12:12:05 by abeauvoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

static inline void	flush_buffer(t_ls *info, size_t len)
{
	ft_putstr(info->buf);
	ft_bzero(info->buf, len);
	info->a = info->buf;
}

inline void			bufferize_str(t_ls *info, const char *str, int len)
{
	if (info->z - info->a < len)
		flush_buffer(info, info->a + 1 - info->buf);
	ft_strcpy(info->a, str);
	info->a += len;
}

inline void			bufferize_char(t_ls *info, char c)
{
	if (info->a == info->z)
		flush_buffer(info, FT_LS_BUFSIZ);
	*(info->a++) = c;
}

char				*ft_ultoa(char *ptr, unsigned long val)
{
	long	sval;

	if (val < 10)
		*--ptr = TO_CHAR(val);
	else
	{
		if (val > LONG_MAX)
		{
			*--ptr = TO_CHAR(val % 10);
			sval = val / 10;
		}
		else
			sval = val;
		while (sval)
		{
			*--ptr = TO_CHAR(sval % 10);
			sval /= 10;
		}
	}
	return (ptr);
}

char				*pad_buffer(char *ptr, size_t len)
{
	while (len--)
		*ptr++ = ' ';
	return (ptr);
}
