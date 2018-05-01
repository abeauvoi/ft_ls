/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abeauvoi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/09 02:28:45 by abeauvoi          #+#    #+#             */
/*   Updated: 2018/05/01 00:55:17 by abeauvoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "ft_ls.h"

static inline bool	display_entry(const char *arg, t_ls_opts options)
{
	if (*arg == '.'
			&& (!(options & (ALL | ALMOST_ALL)) || ((options & ALMOST_ALL)
						&& (arg[1] == 0 || (arg[1] == '.' && arg[2] == 0)))))
		return (false);
	return (true);
}

static inline void	display_entries(t_fileinfo **entries, t_fileinfo **tmp,
		t_ls info)
{
	while (*entries)
	{
		info.outf(*entries);
		if (tmp && (info.options & RECURSIVE)
				&& (*entries)->filetype == DIRECTORY)
			lstpush(tmp, lstpop(entries));
		else
			lstdel_head(entries, &info.entries);
	}
}

static inline void	add_subdirs_to_dirs(t_fileinfo **dirs, t_fileinfo **tmp)
{
	t_fileinfo	*ptr;

	if (!*tmp)
		return ;
	ptr = *tmp;
	while (ptr->next)
		ptr = ptr->next;
	ptr->next = (*dirs);
	(*dirs) = (*tmp);
	(*tmp) = NULL;
}

void				test(t_ls info, t_fileinfo *entries, t_fileinfo *dirs)
{
	DIR				*dirp;
	struct dirent	*de;
	t_fileinfo		*fp;
	t_fileinfo		*tmp;
	size_t			btotal;

	display_entries(&entries, NULL, info);
	while (dirs)
	{
		if (!(dirp = opendir(dirs->path)))
		{
			ft_perror(dirs->name);
			lstdel_head(&dirs, &info.dirs);
		}
		else
		{
			if (info.nb_dirs > 1)
				ft_printf("%s:\n", dirs->path);
			btotal = 0;
			tmp = NULL;
			while ((de = readdir(dirp)) != NULL)
			{
				if (display_entry(de->d_name, info.options))
				{
					fp = init_node(dirs, de);
					lstinsert(&entries, fp, info);
					if (fp->filetype == DIRECTORY)
						++info.nb_dirs;
					btotal += fp->sbuf.st_blocks;
				}
			}
			lstdel_head(&dirs, &info.dirs);
			if (info.options & LONG_LIST && entries)
				ft_printf("total %llu\n", btotal);
			display_entries(&entries, &tmp, info);
			add_subdirs_to_dirs(&dirs, &tmp);
			if (dirs)
				ft_putchar('\n');
			if (closedir(dirp) == -1)
				ft_perror(dirs->path);
		}
	}
}
