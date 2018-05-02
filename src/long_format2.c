/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   long_format2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abeauvoi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/01 06:04:32 by abeauvoi          #+#    #+#             */
/*   Updated: 2018/05/02 12:05:01 by abeauvoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "ft_printf.h"
#include "ft_ls.h"

/*char*/void	/***/print_user/*_or_group*/(uid_t uid)/*(unsigned long id, const char *str,
									   int max_width, char *bufp)*/
{
	//int		len;
	//char		buf[INT_BUFSIZE_BOUND(id) + 1];
	//char		*p;
	//size_t	pad;
	struct passwd	*pwd;

	pwd = getpwuid(uid);
	if (pwd)
		// p = (char*)str;
		// len = ft_strlen(p);
		ft_printf("%s ", pwd->pw_name);
	else
		// p = buf + sizeof(buf) - 1;
		// *p = 0;
		// len = (size_t)(p - ft_ultoa(p, id));
		ft_printf("%lu ", uid);
	// pad = MAX(max_width - len, 0);
	// bufp = pad_buffer(bufp, pad);
	// ft_strcpy(bufp, p);
	// bufp[len] = ' ';
	// return (bufp + len + 1);
}

/*char**/void	print_group(gid_t gid)/*struct group *grp,
										uint8_t max_width, char *bufp)*/
{
	//size_t	len;
	//char		gbuf[INT_BUFSIZE_BOUND(gid_t) + 1];
	//char		*p;
	struct group	*grp;

	grp = getgrgid(gid);
	if (grp)
		// len = ft_strlen(grp->gr_name);
		// bufp = pad_buffer(bufp, max_width - len);
		// ft_strcpy(bufp, grp->gr_name);
		ft_printf("%s ", grp->gr_name);
	else
		// p = gbuf + sizeof(gbuf) - 1;
		// *p = 0;
		// len = (size_t)(p - ft_ultoa(p, uid));
		// bufp = pad_buffer(bufp, max_width - len);
		// ft_strcpy(bufp, gbuf);
		ft_printf("%lu ", gid);
	// bufp[len] = ' ';
	// return (bufp);
}

void	print_inode(t_fileinfo *entry)
{
//	char	buf[INT_BUFSIZE_BOUND(ino_t) + 1];
//	char	*p;
//	int		len;
//	int		pad;
	
	if (entry->stat_ok && entry->sbuf.st_ino)
//		p = buf + sizeof(buf) - 1;
//		*p = 0;
//		len = (p - ft_ultoa(p, inode);
		ft_printf("%ju ", entry->sbuf.st_ino);
	else
		// p = "?";
		// len = 1;
		ft_printf("%s ", "?");
//	pad = MAX(max_width - len, 0);
//	bufp = pad_buffer(bufp, pad);
//	ft_strcpy(bufp, p);
//	bufp[len] = ' ';
//	return (bufp + len + 1);
}

void	print_filename(t_fileinfo *entry)
{
	char	lnbuf[256];
	ssize_t	len;

	// ft_strcpy(bufp, entry->name);
	// bufp += entry->namlen;
	if (entry->filetype == SYMBOLIC_LINK)
	{
		len = readlink(entry->path, lnbuf, sizeof(lnbuf));
		if (len < 0)
		{
			// *bufp++ = '\n';
			ft_printf("%s\n", entry->name);
			return /*(bufp)*/;
		}
		// ft_strcpy(bufp, " -> ");
		// bufp += 4;
		if (len > 255)
		{
			lnbuf[252] = '.';
			lnbuf[253] = '.';
			lnbuf[254] = '.';
			lnbuf[255] = 0;
		}
		else
			lnbuf[len] = 0;
		// ft_strcpy(bufp, lnbuf);
		// bufp[len] = '\n';
		// return (bufp + len + 1);
		ft_printf("%s -> %s\n", entry->name, lnbuf);
	}
	else
		ft_printf("%s\n", entry->name);
}

/*char*/void	/***/print_size(t_fileinfo *entry)/*(char *bufp, int max_width_major, int max_width_minor, int max_width)*/
{
	//char		buf[INT_BUFSIZE_BOUND(dev_t) + 1];
	//char		*p;
	//int		len;
	//int		pad;
	//
	//p = buf + sizeof(buf) - 1;
	//*p = 0;
	if (entry->filetype == CHARDEV || entry->filetype == BLOCKDEV)
		//len = p - ft_ultoa(p, MAJOR(entry->sbuf.st_rdev));
		//pad = MAX(max_width_major - len, 0);
		//bufp = pad_buffer(bufp, pad);
		//ft_strcpy(bufp, buf);
		//bufp += len;
		//*bufp++ = ',';
		//*bufp++ = ' ';
		//ft_bzero(buf, sizeof(buf) -1);
		//len = p - ft_ultoa(p, MINOR(entry->sbuf.st_rdev));
		//pad = MAX(max_width_minor - len, 0);
		ft_printf("%u, %u ", MAJOR(entry->sbuf.st_rdev),
				MINOR(entry->sbuf.st_rdev));
	else
		//len = p - ft_ultoa(p, entry->sbuf.st_size));
		//pad = MAX(max_width - len, 0);
		ft_printf("%u ", entry->sbuf.st_size);
	//bufp = pad_buffer(bufp, pad);
	//ft_strcpy(bufp, buf);
	//bufp[len] = ' ';
	//return (bufp + len + 1);
}
