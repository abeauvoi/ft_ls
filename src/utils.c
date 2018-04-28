/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abeauvoi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/11 02:58:33 by abeauvoi          #+#    #+#             */
/*   Updated: 2018/04/28 00:52:48 by abeauvoi         ###   ########.fr       */
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

bool		rev_cmp(t_fileinfo *arg1, t_fileinfo *arg2, t_ls_opts options)
{
	long	diff;

	if ((options & MODIF_SORT
				&& (diff = arg1->sbuf.st_mtime - arg2->sbuf.st_mtime) != 0)
			|| (options & SIZE_SORT
				&& (diff = arg1->sbuf.st_size - arg2->sbuf.st_size) != 0))
			return (diff < 0);
	return (ft_strcmp(arg1->path, arg2->path) > 0);
}

bool		cmp(t_fileinfo *arg1, t_fileinfo *arg2, t_ls_opts options)
{
	long	diff;

	if ((options & MODIF_SORT
				&& (diff = arg1->sbuf.st_mtime - arg2->sbuf.st_mtime) != 0)
			|| (options & SIZE_SORT
				&& (diff = arg1->sbuf.st_size - arg2->sbuf.st_size) != 0))
			return (diff > 0);
	return (ft_strcmp(arg1->path, arg2->path) < 0);
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

void			bubble_sort_argv(const char **argv)
{
	bool		sorted;
	const char	**save_argv;
	const char	*tmp;

	sorted = false;
	save_argv = argv;
	while (!sorted)
	{
		argv = save_argv + 1;
		sorted = true;
		while (*argv)
		{
			if (ft_strcmp(*argv, *save_argv) < 0)
			{
				tmp = *argv;
				*argv = *save_argv;
				*save_argv = tmp;
				sorted = false;
			}
			++argv;
		}
		++save_argv;
	}
}
