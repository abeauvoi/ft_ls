/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   long_format.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abeauvoi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/09 04:51:12 by abeauvoi          #+#    #+#             */
/*   Updated: 2018/04/11 04:50:36 by jolabour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/stat.h>
#include <sys/types.h>
#include <pwd.h>
#include <grp.h>
#include <uuid/uuid.h>
#include <time.h>
#include "ft_ls.h"

void		ft_putstr_space(const char *str)
{
	ft_putstr(str);
	ft_putchar(' ');
}

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
	ft_putchar(FILETYPE[(buf.st_mode & S_IFMT) >> 13]);
	ft_putstr(rwx[(buf.st_mode & S_IRWXU) >> 6]);
	ft_putstr(rwx[(buf.st_mode & S_IRWXG) >> 3]);
	ft_putstr_space(rwx[(buf.st_mode & S_IRWXO)]);
	ft_putstr_space(ft_itoa((int)buf.st_nlink));
	ft_putstr_space(pwd->pw_name);
	ft_putstr_space(grp->gr_name);
	ft_putstr_space(ft_itoa((int)buf.st_size));
	ft_putstr_space(ctime((time_t*)&buf.st_mtime));
	ft_putstr_space(arg);
}
