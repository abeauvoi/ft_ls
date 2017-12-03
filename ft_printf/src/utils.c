/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_1.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abeauvoi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/22 11:12:28 by abeauvoi          #+#    #+#             */
/*   Updated: 2017/09/12 17:33:47 by abeauvoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "ft_printf.h"

size_t			ft_wcs_bc(const t_wchar *s, int prec)
{
	ssize_t		bc;

	bc = 0;
	if (prec == -1)
	{
		while (*s)
			bc += ft_wchar_bc(*s++);
		return ((size_t)bc);
	}
	else
		while (*s && (bc += ft_wchar_bc(*s)) < prec)
			++s;
	return (bc > prec ? (size_t)(bc - ft_wchar_bc(*s)) : (size_t)bc);
}

size_t			ft_wchar_bc(t_wchar ch)
{
	if (ch < 0x80)
		return (1);
	else if (ch < 0x800)
		return (2);
	else if (ch < 0x10000)
		return (3);
	else
		return (4);
}

/*
** <<<<<<<<<<<<
** Building the header character : (e.g. nbytes == 3)
** utf8header = ~((1 << (8 - nbytes)) - 1);
** 1 << (8 - 3) ==> 0010.0000 - 1 ==> 0001.1111 ~ ==> 1110.0000
** -----------
** ch >> (--nbytes * 6) | utf8header : (e.g. ch == 0x11010.1111.1111)
** ch >> (2 * 6) ==> 1 | utf8header ==> 1110.0001
** >>>>>>>>>>>>
** The following characters are created in similar fashion.
*/

void			wchar_to_utf8(t_ftpf_buf *buffer, t_wchar ch)
{
	int			nbytes;
	int			i;
	t_uc		utf8header;

	if (ch < 0x80 || MB_CUR_MAX == 1)
	{
		copy_to_buf(buffer, (char)ch);
		return ;
	}
	nbytes = ft_wchar_bc(ch);
	utf8header = ~((1 << (8 - nbytes)) - 1);
	copy_to_buf(buffer, (ch >> (--nbytes * 6)) | utf8header);
	i = 1;
	while (nbytes--)
	{
		copy_to_buf(buffer, ((ch >> (nbytes * 6)) & 0x3f) | 0x80);
		if (++i == MB_CUR_MAX)
			return ;
	}
}
