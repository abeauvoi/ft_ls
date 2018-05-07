/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abeauvoi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/03 01:13:56 by abeauvoi          #+#    #+#             */
/*   Updated: 2018/05/07 05:50:42 by abeauvoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

char	get_filetype_indicator(t_fileinfo *entry)
{
	if (entry->filetype == DIRECTORY)
		return ('/');
	else if (entry->filetype == NORMAL
			&& (entry->sbuf.st_mode & (S_IXUSR | S_IXGRP | S_IXOTH)))
		return ('*');
	else if (entry->filetype == SYMBOLIC_LINK)
		return ('@');
	else if (entry->filetype == SOCK)
		return ('=');
	else if (entry->filetype == WHITEOUT)
		return ('%');
	else if (entry->filetype == FIFO)
		return ('|');
	return (0);
}

char	*itob(char *mbuf, uintmax_t val, int max_width, bool is_negative)
{
	char	buf[INT_BUFSIZE_BOUND(uintmax_t) + 1];
	char	*a;
	char	*z;
	size_t	len;

	z = buf + sizeof(buf) - 1;
	*z = 0;
	a = ft_ultoa(z, val, is_negative);
	len = z - a;
	mbuf = pad_buffer(mbuf, MAX(max_width - len, 0));
	ft_memcpy(mbuf, a, len);
	mbuf += len;
	return (mbuf);
}

int		numstrlen(intmax_t n)
{
	int		l;

	l = !n;
	while (n)
	{
		n /= 10;
		++l;
	}
	return (l);
}

void	save_col_widths(t_ls *info)
{
	info->lfmt_cwidth[INODE_COL] = numstrlen(info->max_inode);
	info->lfmt_cwidth[BLOCKS_COL] = numstrlen(info->max_block_size);
	info->lfmt_cwidth[NLINKS_COL] = numstrlen(info->max_nlink);
	info->lfmt_cwidth[OWNER_COL] = MAX(info->lfmt_cwidth[OWNER_COL],
			numstrlen(info->max_uid));
	info->lfmt_cwidth[GROUP_COL] = MAX(info->lfmt_cwidth[GROUP_COL],
			numstrlen(info->max_gid));
	info->lfmt_cwidth[MAJOR_DEV_COL] = numstrlen(info->max_major);
	info->lfmt_cwidth[MINOR_DEV_COL] = numstrlen(info->max_minor);
	info->lfmt_cwidth[FILE_SIZE_COL] =
		MAX(numstrlen(info->max_file_size), info->lfmt_cwidth[MAJOR_DEV_COL]
				+ info->lfmt_cwidth[MINOR_DEV_COL] + 2);
}

char	*ft_strcpy_non_printable_chars(char *dst, const char *src)
{
	char	*d;

	d = dst;
	while (*src)
	{
		if (!ft_isprint(*src))
			*d = '?';
		else
			*d = *src;
		++d;
		++src;
	}
	*d = *src;
	return (dst);
}
