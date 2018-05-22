/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abeauvoi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/02 06:09:11 by abeauvoi          #+#    #+#             */
/*   Updated: 2018/05/22 21:25:52 by abeauvoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "ft_ls.h"

inline void	ft_ls_flush_buffer(t_ls *info)
{
	*(info->a) = 0;
	write(1, info->buf, info->a - info->buf);
	info->a = info->buf;
}

inline void	strtobuf(t_ls *info, const char *str, int len)
{
	if (info->z - info->a < len)
		ft_ls_flush_buffer(info);
	ft_strcpy(info->a, str);
	info->a += len;
}

inline void	chartobuf(t_ls *info, char c)
{
	if (info->a == info->z)
		ft_ls_flush_buffer(info);
	*(info->a++) = c;
}

char		*ft_ultoa(char *ptr, unsigned long val, bool is_negative)
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

char		*pad_buffer(char *ptr, size_t len)
{
	while (len-- > 0)
		*ptr++ = ' ';
	return (ptr);
}
