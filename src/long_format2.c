/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   long_format2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abeauvoi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/01 06:04:32 by abeauvoi          #+#    #+#             */
/*   Updated: 2018/05/21 04:02:37 by abeauvoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "ft_ls.h"

inline char	*print_user(t_fileinfo *entry, char *bufp, uint8_t max_width)
{
	if (entry->user_name)
	{
		ft_strcpy(bufp, entry->user_name);
		bufp += entry->user_name_length;
		bufp = pad_buffer(bufp,
				MAX((int)(max_width - entry->user_name_length), 0));
	}
	else if (entry->stat_ok)
		bufp = itob(bufp, entry->sbuf.st_uid, max_width, 0);
	else
	{
		bufp = pad_buffer(bufp, MAX(max_width - 1, 0));
		*bufp++ = '?';
	}
	*bufp++ = ' ';
	*bufp++ = ' ';
	return (bufp);
}

inline char	*print_group(t_fileinfo *entry, char *bufp, uint8_t max_width)
{
	if (entry->group_name)
	{
		ft_strcpy(bufp, entry->group_name);
		bufp += entry->group_name_length;
		bufp = pad_buffer(bufp,
				MAX((int)(max_width - entry->group_name_length), 0));
	}
	else if (entry->stat_ok)
		bufp = itob(bufp, entry->sbuf.st_gid, max_width, 0);
	else
	{
		bufp = pad_buffer(bufp, MAX(max_width - 1, 0));
		*bufp++ = '?';
	}
	*bufp++ = ' ';
	*bufp++ = ' ';
	return (bufp);
}

inline char	*print_inode(t_fileinfo *entry, char *bufp, uint8_t max_width)
{
	if (entry->stat_ok && entry->sbuf.st_ino)
		bufp = itob(bufp, entry->sbuf.st_ino, max_width, 0);
	else
	{
		bufp = pad_buffer(bufp, max_width - 1);
		*bufp++ = '?';
	}
	*bufp++ = ' ';
	return (bufp);
}

inline char	*print_filename(t_fileinfo *entry, char *bufp, t_ls info)
{
	ssize_t	len;

	ft_strcpy_non_printable_chars(bufp, entry->name);
	bufp += entry->namlen;
	if (info.options & FILETYPE_INDICATOR
			&& (*bufp = get_filetype_indicator(entry->stat_ok,
					entry->sbuf.st_mode, entry->filetype)) != 0)
		++bufp;
	if (entry->stat_ok ? S_ISLNK(entry->sbuf.st_mode) :
			entry->filetype == SYMBOLIC_LINK)
	{
		ft_memcpy(bufp, " -> ", 4);
		bufp += 4;
		len = readlink(entry->path, bufp, PATH_MAX);
		bufp += len;
	}
	*bufp++ = '\n';
	*bufp = 0;
	return (bufp);
}

inline char	*print_size(t_fileinfo *entry, char *bufp, t_ls info)
{
	if (entry->stat_ok ?
			S_ISCHR(entry->sbuf.st_mode) || S_ISBLK(entry->sbuf.st_mode) :
			entry->filetype == CHARDEV || entry->filetype == BLOCKDEV)
	{
		bufp = itob(bufp, MAJOR(entry->sbuf.st_rdev),
				info.lfmt_cwidth[MAJOR_DEV_COL],
				MAJOR(entry->sbuf.st_rdev) < 0);
		*bufp++ = ',';
		*bufp++ = ' ';
		bufp = itob(bufp, MINOR(entry->sbuf.st_rdev),
				info.lfmt_cwidth[MINOR_DEV_COL],
				MINOR(entry->sbuf.st_rdev) < 0);
	}
	else if (entry->filetype != UNKNOWN || entry->sbuf.st_mode)
		bufp = itob(bufp, entry->sbuf.st_size, info.lfmt_cwidth[FILE_SIZE_COL],
				entry->sbuf.st_size < 0);
	else
	{
		bufp = pad_buffer(bufp, MAX(info.lfmt_cwidth[FILE_SIZE_COL] - 1, 0));
		*bufp++ = '?';
	}
	*bufp++ = ' ';
	return (bufp);
}
