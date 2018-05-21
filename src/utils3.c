/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abeauvoi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/03 01:13:56 by abeauvoi          #+#    #+#             */
/*   Updated: 2018/05/21 04:10:24 by abeauvoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

/*
** Reminder: the 'type' variable gets its data from the readdir function.
*/

char	get_filetype_indicator(bool stat_ok, mode_t mode, enum e_filetype type)
{
	char	c;

	if (stat_ok ? S_ISREG(mode) : type == NORMAL)
		c = (stat_ok && (mode & (S_IXUSR | S_IXGRP | S_IXOTH)) ? '*' : '0');
	else if (stat_ok ? S_ISDIR(mode) : type == DIRECTORY)
		c = '/';
	else if (stat_ok ? S_ISLNK(mode) : type == SYMBOLIC_LINK)
		c = '@';
	else if (stat_ok ? S_ISSOCK(mode) : type == SOCKET)
		c = '=';
	else if (stat_ok ? S_ISWHT(mode) : type == WHITEOUT)
		c = '%';
	else if (stat_ok ? S_ISFIFO(mode) : type == FIFO)
		c = '|';
	else
		c = 0;
	return (c);
}

char	*itob(char *mbuf, uintmax_t val, int max_width, bool is_negative)
{
	char	buf[INT_BUFSIZE_BOUND(uintmax_t) + 1];
	char	*a;
	char	*z;
	int		len;

	z = buf + sizeof(buf) - 1;
	*z = 0;
	a = ft_ultoa(z, val, is_negative);
	len = z - a;
	mbuf = pad_buffer(mbuf, MAX(max_width - len, 0));
	ft_memcpy(mbuf, a, len);
	mbuf += len;
	return (mbuf);
}

/*
** l = 1 if n == 0;
*/

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
	if (info->found_major_minor_dev)
	{
		info->lfmt_cwidth[MAJOR_DEV_COL] = numstrlen(info->max_major);
		info->lfmt_cwidth[MINOR_DEV_COL] = numstrlen(info->max_minor);
		info->lfmt_cwidth[FILE_SIZE_COL] =
			MAX(numstrlen(info->max_file_size), info->lfmt_cwidth[MAJOR_DEV_COL]
					+ info->lfmt_cwidth[MINOR_DEV_COL] + 2);
	}
	else
		info->lfmt_cwidth[FILE_SIZE_COL] = numstrlen(info->max_file_size);
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
