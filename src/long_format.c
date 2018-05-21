/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   long_format.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abeauvoi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/09 04:51:12 by abeauvoi          #+#    #+#             */
/*   Updated: 2018/05/21 06:26:03 by abeauvoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/xattr.h>
#include <sys/acl.h>
#include "ft_ls.h"

static inline char	get_xattr(const char *path)
{
	acl_t		acl;
	acl_entry_t	entry;
	int			ret;

	acl = acl_get_file(path, ACL_TYPE_EXTENDED);
	if (!acl && acl_get_entry(acl, ACL_FIRST_ENTRY, &entry) == -1)
	{
		acl_free(acl);
		acl = NULL;
	}
	if ((ret = listxattr(path, NULL, 0, XATTR_NOFOLLOW)) < 0
			&& (errno == EPERM || errno == EACCES || errno == EFAULT))
	{
		errno = 0;
		return (' ');
	}
	else if (ret > 0)
		return ('@');
	else if (acl)
		return ('+');
	return (' ');
}

static inline char	get_usr_exec_rights(mode_t mode)
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

static inline char	get_grp_exec_rights(mode_t mode)
{
	t_u16		ret;

	if ((ret = mode & (S_IXGRP | S_ISGID)))
	{
		if (ret == S_IXGRP)
			return ('x');
		else if (ret == S_ISGID)
			return ('S');
		else
			return ('s');
	}
	return ('-');
}

static inline char	*print_filemode(t_fileinfo *entry, char *bufp)
{
	char				modebuf[11 + 1];
	unsigned			i;
	static char			*rwx[8] = {"---", "--x", "-w-", "-wx", "r--", "r-x",
		"rw-", "rwx"};

	i = (entry->stat_ok ? (entry->sbuf.st_mode & S_IFMT) >> 12
			: entry->filetype);
	modebuf[0] = FILETYPE_LETTER[(entry->stat_ok && i > 2 ? (i >> 1) + 1 : i)];
	if (entry->stat_ok)
	{
		ft_strcpy(modebuf + 1, rwx[(entry->sbuf.st_mode & S_IRWXU) >> 6]);
		modebuf[3] = get_usr_exec_rights(entry->sbuf.st_mode);
		ft_strcpy(modebuf + 4, rwx[(entry->sbuf.st_mode & S_IRWXG) >> 3]);
		modebuf[6] = get_grp_exec_rights(entry->sbuf.st_mode);
		ft_strcpy(modebuf + 7, rwx[entry->sbuf.st_mode & S_IRWXO]);
		modebuf[9] = get_others_exec_rights(entry->sbuf.st_mode);
		modebuf[10] = get_xattr(entry->path);
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

void				long_format(t_fileinfo *entry, t_ls *info)
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
