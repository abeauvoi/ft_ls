/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   long_format.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abeauvoi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/09 04:51:12 by abeauvoi          #+#    #+#             */
/*   Updated: 2018/05/02 12:06:53 by abeauvoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <time.h>
#include <unistd.h>
#include <sys/xattr.h>
#include <sys/acl.h>
#include <stdlib.h>
#include <sys/types.h>
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

static void		print_filemode(t_fileinfo *entry, char *buf)
{
	char				modebuf[11 + 1];
	static char			*rwx[8] = {"---", "--x", "-w-", "-wx", "r--", "r-x",
		"rw-", "rwx"};

	modebuf[0] = FILETYPE_LETTER[entry->filetype];
	if (entry->stat_ok)
	{
		strcpy(modebuf + 1, rwx[(entry->sbuf.st_mode & S_IRWXU) >> 6]);
		modebuf[3] = get_usr_exec_rights(entry->sbuf.st_mode);
		strcpy(modebuf + 4, rwx[(entry->sbuf.st_mode & S_IRWXG) >> 3]);
		modebuf[6] = get_grp_exec_rights(entry->sbuf.st_mode);
		strcpy(modebuf + 7, rwx[entry->sbuf.st_mode & S_IRWXO]);
		modebuf[10] = get_xattr(entry->path, entry->sbuf.st_mode);
	}
	else
		ft_memset(modebuf + 1, '?', 10);
	modebuf[11] = 0;
	ft_printf("%s ", modebuf);
	(void)buf;
	//ft_strcpy(bufp, modebuf);
	//bufp += 12;
	//return (bufp);
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
** - Date
** - File name
*/

void			long_format(t_fileinfo *entry, t_ls info)
{
	char	buf[INT_BUFSIZE_BOUND(ino_t) + INT_BUFSIZE_BOUND(blkcnt_t)
		+ INT_BUFSIZE_BOUND(nlink_t) + INT_BUFSIZE_BOUND(uid_t)
		+ INT_BUFSIZE_BOUND(gid_t) + INT_BUFSIZE_BOUND(dev_t)
		+ INT_BUFSIZE_BOUND(dev_t) + entry->namlen + 303];
	char	*bufp;

	bufp = buf;
	if (info.options & PRINT_INODE)
		print_inode(entry);
	if (info.options & PRINT_BLOCKS)
		print_blocks(entry);
	print_filemode(entry, buf);
	ft_printf("%u ", entry->sbuf.st_nlink);
	print_user(entry->sbuf.st_uid);
	print_group(entry->sbuf.st_gid);
	print_size(entry);
	ft_printf("%.12s ", ctime((time_t*)&entry->sbuf.st_mtime) + 4);
	/*bufp = */print_filename(entry);
//	*bufp = 0;
//	bufferize_str(info, buf, len);
}
