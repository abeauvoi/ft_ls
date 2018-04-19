/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   long_format.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abeauvoi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/09 04:51:12 by abeauvoi          #+#    #+#             */
/*   Updated: 2018/04/19 00:30:14 by abeauvoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/types.h>
#include <pwd.h>
#include <grp.h>
#include <uuid/uuid.h>
#include <time.h>
#include "ft_ls.h"

void	long_format(t_fileinfo *entry)
{
	struct passwd		*pwd;
	struct group		*grp;
	static const char	*rwx[8] = {"---", "--x", "-w-", "-wx", "r--", "r-x",
		"rw-", "rwx"};

	pwd = getpwuid(entry->sbuf.st_uid);
	grp = getgrgid(entry->sbuf.st_gid);
	ft_printf("%c%s%s%s %3u %s  %s %6u %.12s %s\n",
			FILETYPE[entry->filetype],
			rwx[(entry->sbuf.st_mode & S_IRWXU) >> 6],
			rwx[(entry->sbuf.st_mode & S_IRWXG) >> 3],
			rwx[(entry->sbuf.st_mode & S_IRWXO)],
			entry->sbuf.st_nlink,
			pwd->pw_name,
			grp->gr_name,
			entry->sbuf.st_size,
			ctime((time_t*)&entry->sbuf.st_mtimespec.tv_sec) + 4,
			entry->name);
}
