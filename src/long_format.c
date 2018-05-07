/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   long_format.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abeauvoi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/09 04:51:12 by abeauvoi          #+#    #+#             */
/*   Updated: 2018/05/07 02:59:10 by abeauvoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/xattr.h>
#include <sys/acl.h>
#include "ft_ls.h"
#include "ft_printf.h"

static char		get_xattr(const char *path, mode_t mode)
{
	acl_t		acl;

	acl = acl_get_link_np(path, ACL_TYPE_EXTENDED);
	acl_free(acl);
	if (mode & (S_IFREG | S_IFDIR))
	{
		if (listxattr(path, NULL, 0, XATTR_NOFOLLOW))
			return ('@');
		else if (acl)
			return ('+');
	}
	return (' ');
}

static char		get_usr_exec_rights(mode_t mode)
{
	t_u16		ret;

	if ((ret = mode & (S_IXUSR | S_ISUID)))
	{
		if (ret == S_IXUSR)
			return ('x');
		else if (ret == S_ISUID)
			return ('S');
		else
			return ('s');
	}
	return ('-');
}

static char		get_grp_exec_rights(mode_t mode)
{
	t_u16		ret;

	if ((ret = mode & (S_IXGRP | S_ISGID)))
	{
		if (ret == S_IXGRP)
			return ('x');
		else if (ret == S_ISGID)
			return ('T');
		else
			return ('t');
	}
	return ('-');
}

static char		*print_filemode(t_fileinfo *entry, char *bufp)
{
	char				modebuf[11 + 1];
	static char			*rwx[8] = {"---", "--x", "-w-", "-wx", "r--", "r-x",
		"rw-", "rwx"};

	modebuf[0] = FILETYPE_LETTER[entry->filetype];
	if (entry->stat_ok)
	{
		ft_strcpy(modebuf + 1, rwx[(entry->sbuf.st_mode & S_IRWXU) >> 6]);
		modebuf[3] = get_usr_exec_rights(entry->sbuf.st_mode);
		ft_strcpy(modebuf + 4, rwx[(entry->sbuf.st_mode & S_IRWXG) >> 3]);
		modebuf[6] = get_grp_exec_rights(entry->sbuf.st_mode);
		ft_strcpy(modebuf + 7, rwx[entry->sbuf.st_mode & S_IRWXO]);
		modebuf[10] = get_xattr(entry->path, entry->sbuf.st_mode);
	}
	else
		ft_memset(modebuf + 1, '?', 10);
	modebuf[11] = 0;
	ft_strcpy(bufp, modebuf);
	bufp += 11;
	*bufp++ = ' ';
	return (bufp);
}

/*
** In order:
** - Inode number
** - Blocks
** - permissions + ACL/Extended attributes (11)
** - Num. of links
** - User name/UID
** - Group name/GID
** - File size/Major, Minor
** - Timestamp
** - File name
*/

void			long_format(t_fileinfo *entry, t_ls *info)
{
	char	*bufp;
	char	buf[2000];

	save_col_widths(info);
	bufp = buf;
	if (info->options & PRINT_INODE)
		bufp = print_inode(entry, bufp, info->lfmt_cwidth[INODE_COL]);
	if (info->options & PRINT_BLOCKS)
		bufp = print_blocks(entry, bufp, info->lfmt_cwidth[BLOCKS_COL]);
	bufp = print_filemode(entry, bufp);
	bufp = print_nlinks(entry, bufp, info->lfmt_cwidth[NLINKS_COL]);
	bufp = print_user(entry, bufp, info->lfmt_cwidth[OWNER_COL]);
	bufp = print_group(entry, bufp, info->lfmt_cwidth[GROUP_COL]);
	bufp = print_size(entry, bufp, *info);
	bufp = print_time_info(entry, bufp);
	bufp = print_filename(entry, bufp, *info);
	strtobuf(info, buf, bufp - buf);
}
