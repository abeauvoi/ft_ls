/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   long_format.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abeauvoi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/09 04:51:12 by abeauvoi          #+#    #+#             */
/*   Updated: 2018/04/09 07:53:46 by abeauvoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/stat.h>
#include <sys/types.h>
#include <pwd.h>
#include <grp.h>
#include <uuid/uuid.h>
#include <time.h>
#include "ft_ls.h"

void	long_format(const char *arg)
{
	struct stat			buf;
	struct passwd		*pwd;
	struct group		*grp;
	static const char	*rwx[] = {"---", "--x", "-w-", "-wx", "r--", "r-x",
		"rw-", "rwx"};

	lstat(arg, &buf);
	pwd = getpwuid(buf.st_uid);
	grp = getgrgid(buf.st_gid);
	ft_printf("%c%s%s%s %3u %s  %s %6u %.12s %s\n",
			FILETYPE[(buf.st_mode & S_IFMT) >> 13],
			rwx[(buf.st_mode & S_IRWXU) >> 6],
			rwx[(buf.st_mode & S_IRWXG) >> 3],
			rwx[(buf.st_mode & S_IRWXO)],
			buf.st_nlink,
			pwd->pw_name,
			grp->gr_name,
			buf.st_size,
			ctime((time_t*)&buf.st_mtimespec.tv_sec) + 4,
			arg);
}
