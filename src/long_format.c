/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   long_format.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abeauvoi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/09 04:51:12 by abeauvoi          #+#    #+#             */
/*   Updated: 2018/04/27 06:13:44 by abeauvoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/types.h>
#include <pwd.h>
#include <grp.h>
#include <uuid/uuid.h>
#include <time.h>
#include <unistd.h>
#include <sys/xattr.h>
#include <sys/acl.h>
#include "ft_ls.h"

static char		print_exec_rights(mode_t mode, char *rights, uint8_t s,
		char letter)
{
	if ((s == 0 && mode & S_ISUID)
			|| (s == 1 && mode & S_ISGID)
			|| (s == 2 && mode & S_ISVTX))
		return (rights[2] == 'x' ? letter : letter - 32);
	return (rights[2]);
}

static char		print_xattr(const char *path)
{
	acl_t		acl;
	acl_entry_t	tmp;

	acl = acl_get_link_np(path, ACL_TYPE_EXTENDED);
	if (acl && acl_get_entry(acl, ACL_FIRST_ENTRY, &tmp) == -1)
	{
		acl_free(acl);
		acl = NULL;
	}
	if (listxattr(path, NULL, 0, XATTR_NOFOLLOW))
		return ('@');
	else if (acl)
		return ('+');
	else
		return (' ');
}

void	long_format(t_fileinfo *entry)
{
	struct passwd		*pwd;
	char				lnbuf[PATH_MAX + 1];
	ssize_t				len;
	struct group		*grp;
	static char			*rwx[8] = {"---", "--x", "-w-", "-wx", "r--", "r-x",
		"rw-", "rwx"};

	pwd = getpwuid(entry->sbuf.st_uid);
	grp = getgrgid(entry->sbuf.st_gid);
	ft_printf("%c%.2s%c%.2s%c%.2s%c%c %u %s %s ",
			FILETYPE[entry->filetype],
			rwx[(entry->sbuf.st_mode & S_IRWXU) >> 6],
			print_exec_rights(entry->sbuf.st_mode,
				rwx[(entry->sbuf.st_mode & S_IRWXU) >> 6], 0, 's'),
			rwx[(entry->sbuf.st_mode & S_IRWXG) >> 3],
			print_exec_rights(entry->sbuf.st_mode,
				rwx[(entry->sbuf.st_mode & S_IRWXG) >> 3], 1, 's'),
			rwx[entry->sbuf.st_mode & S_IRWXO],
			print_exec_rights(entry->sbuf.st_mode,
				rwx[entry->sbuf.st_mode & S_IRWXO], 2, 't'),
			print_xattr(entry->path),
			entry->sbuf.st_nlink,
			pwd->pw_name,
			grp->gr_name);
	if (entry->filetype == CHARDEV || entry->filetype == BLOCKDEV)
		ft_printf("%u, %u ", MAJOR(entry->sbuf.st_rdev),
				MINOR(entry->sbuf.st_rdev));
	else
		ft_printf("%u ", entry->sbuf.st_size);
	ft_printf("%.12s ", ctime((time_t*)&entry->sbuf.st_mtime) + 4);
	if (entry->filetype == SYMBOLIC_LINK)
	{
		len = readlink(entry->path, lnbuf, sizeof(lnbuf));
		lnbuf[len] = 0;
		ft_printf("%s -> %s\n", entry->name, lnbuf);
	}
	else
		ft_printf("%s\n", entry->name);
}
