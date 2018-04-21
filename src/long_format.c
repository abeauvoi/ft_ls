/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   long_format.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abeauvoi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/09 04:51:12 by abeauvoi          #+#    #+#             */
/*   Updated: 2018/04/21 05:46:21 by abeauvoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/types.h>
#include <pwd.h>
#include <grp.h>
#include <uuid/uuid.h>
#include <time.h>
#include <unistd.h>
#include "ft_ls.h"

void	long_format(t_fileinfo *entry)
{
	struct passwd		*pwd;
	char				lnbuf[PATH_MAX + 1];
	ssize_t				len;
	struct group		*grp;
	static const char	*rwx[8] = {"---", "--x", "-w-", "-wx", "r--", "r-x",
		"rw-", "rwx"};

	pwd = getpwuid(entry->sbuf.st_uid);
	grp = getgrgid(entry->sbuf.st_gid);
	ft_printf("%c%s%s%s %u %s  %s ",
			FILETYPE[entry->filetype],
			rwx[(entry->sbuf.st_mode & S_IRWXU) >> 6],
			rwx[(entry->sbuf.st_mode & S_IRWXG) >> 3],
			rwx[(entry->sbuf.st_mode & S_IRWXO)],
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
