/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   long_format3.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abeauvoi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/02 04:46:49 by abeauvoi          #+#    #+#             */
/*   Updated: 2018/05/21 03:56:55 by abeauvoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <time.h>
#include "ft_ls.h"

inline char	*print_blocks(t_fileinfo *entry, char *bufp, uint8_t max_width)
{
	if (entry->stat_ok)
		bufp = itob(bufp, entry->sbuf.st_blocks, max_width,
				entry->sbuf.st_blocks < 0);
	else
	{
		bufp = pad_buffer(bufp, max_width - 1);
		*bufp++ = '?';
	}
	*bufp++ = ' ';
	return (bufp);
}

inline char	*print_nlinks(t_fileinfo *entry, char *bufp, uint8_t max_width)
{
	if (entry->stat_ok)
		bufp = itob(bufp, entry->sbuf.st_nlink, max_width,
				entry->sbuf.st_nlink < 0);
	else
	{
		bufp = pad_buffer(bufp, MAX(max_width - 1, 0));
		*bufp++ = '?';
	}
	*bufp++ = ' ';
	return (bufp);
}

/*
** Example output of ctime : "Thu Nov 24 18:22:48 1986\n\0"
*/

inline char	*print_time_info(t_fileinfo *entry, char *bufp)
{
	time_t	epoch;
	char	*timestamp;

	if (entry->stat_ok)
	{
		timestamp = ctime((time_t *)&entry->sbuf.st_mtime) + 4;
		ft_memcpy(bufp, timestamp, 7);
		bufp += 7;
		timestamp += 7;
		if (time(&epoch) != -1
				&& epoch - entry->sbuf.st_mtime > SECONDS_IN_SIX_MONTHS)
			ft_memcpy(bufp, timestamp + 8, 5);
		else
			ft_memcpy(bufp, timestamp, 5);
		bufp += 5;
	}
	else
	{
		bufp = pad_buffer(bufp, 11);
		*bufp++ = '?';
	}
	*bufp++ = ' ';
	return (bufp);
}

inline char	get_others_exec_rights(mode_t mode)
{
	t_u16	ret;

	if ((ret = mode & (S_ISVTX | S_IXOTH)))
	{
		if (ret == S_IXOTH)
			return ('x');
		else if (ret == S_ISVTX)
			return ('T');
		else
			return ('t');
	}
	return ('-');
}
