/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abeauvoi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/11 02:58:33 by abeauvoi          #+#    #+#             */
/*   Updated: 2018/05/23 00:06:37 by abeauvoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "ft_ls.h"

char			*concat_path(const char *path, const char *filename,
		size_t path_len, size_t filename_len)
{
	char		*join;
	size_t		total_len;
	bool		need_slash;

	if (path[path_len - 1] == '/')
	{
		total_len = 1;
		need_slash = false;
	}
	else
	{
		total_len = 2;
		need_slash = true;
	}
	total_len += path_len + filename_len;
	if (!(join = malloc(total_len)))
		return (NULL);
	ft_strcpy(join, path);
	if (need_slash)
		join[path_len] = '/';
	ft_strcpy(join + path_len + need_slash, filename);
	return (join);
}

bool			rev_cmp(t_fileinfo *arg1, t_fileinfo *arg2, t_ls_opts options)
{
	long	diff;

	if ((options & MODIF_SORT
				&& (diff = arg1->sbuf.st_mtime - arg2->sbuf.st_mtime) != 0)
			|| (options & SIZE_SORT
				&& (diff = arg1->sbuf.st_size - arg2->sbuf.st_size) != 0))
		return (diff < 0);
	return (ft_strcmp(arg1->path, arg2->path) > 0);
}

bool			cmp(t_fileinfo *arg1, t_fileinfo *arg2, t_ls_opts options)
{
	long	diff;

	if ((options & MODIF_SORT
				&& (diff = arg1->sbuf.st_mtime - arg2->sbuf.st_mtime) != 0)
			|| (options & SIZE_SORT
				&& (diff = arg1->sbuf.st_size - arg2->sbuf.st_size) != 0))
		return (diff > 0);
	return (ft_strcmp(arg1->path, arg2->path) < 0);
}

enum e_filetype	get_filetype(mode_t mode)
{
	if (S_ISFIFO(mode))
		return (FIFO);
	else if (S_ISCHR(mode))
		return (CHARDEV);
	else if (S_ISDIR(mode))
		return (DIRECTORY);
	else if (S_ISBLK(mode))
		return (BLOCKDEV);
	else if (S_ISREG(mode))
		return (NORMAL);
	else if (S_ISLNK(mode))
		return (SYMBOLIC_LINK);
	else if (S_ISSOCK(mode))
		return (SOCKET);
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
