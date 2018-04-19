/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abeauvoi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/11 02:58:33 by abeauvoi          #+#    #+#             */
/*   Updated: 2018/04/19 05:45:58 by abeauvoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

char		*concat_path(const char *path, const char *arg, size_t len_1,
		size_t len_2)
{
	char	*join;

	if (!(join = ft_strnew(len_1 + len_2 + 1)))
		return (NULL);
	ft_strncpy(join, path, len_1);
	if (join[len_1 - 1] != '/')
	{
		join[len_1++] = '/';
		join[len_1] = 0;
	}
	ft_strncpy(join + len_1, arg, len_2); 
	return (join);
}

t_bool		cmp(t_fileinfo *arg1, t_fileinfo *arg2, t_ls_opts options)
{
	t_bool	t;

	t = (ft_strcmp(arg1->name, arg2->name) < 0);
	if (options & MODIF_SORT)
		t = ((arg1->sbuf.st_mtime) > (arg2->sbuf.st_mtime));
	else if (options & SIZE_SORT)
		t = ((arg1->sbuf.st_size) > (arg2->sbuf.st_size));
	return (t);
}

enum e_filetype	get_filetype(mode_t protection)
{
	if (S_ISFIFO(protection))
		return (FIFO);
	else if (S_ISCHR(protection))
		return (CHARDEV);
	else if (S_ISDIR(protection))
		return (DIRECTORY);
	else if (S_ISBLK(protection))
		return (BLOCKDEV);
	else if (S_ISREG(protection))
		return (NORMAL);
	else if (S_ISLNK(protection))
		return (SYMBOLIC_LINK);
	else if (S_ISSOCK(protection))
		return (SOCK);
	return (UNKNOWN);
}
