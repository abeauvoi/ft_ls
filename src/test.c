/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abeauvoi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/09 02:28:45 by abeauvoi          #+#    #+#             */
/*   Updated: 2018/04/28 07:06:39 by abeauvoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "ft_ls.h"

static bool			display_entry(const char *arg, t_ls_opts options)
{
	if (*arg == '.'
			&& (!(options & (ALL | ALMOST_ALL)) || ((options & ALMOST_ALL)
						&& (arg[1] == 0 || (arg[1] == '.' && arg[2] == 0)))))
		return (false);
	return (true);
}

static inline void	display_entries(t_fileinfo **entries, t_fileinfo **tmp,
		void (*outf)(t_fileinfo *), t_ls_opts options)
{
	while (*entries)
	{
		outf(*entries);
		if (tmp && options & RECURSIVE && (*entries)->filetype == DIRECTORY)
		{
			lstpush(tmp, lstpop(entries));
		}
		else
			lstdel_head(entries);
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

	display_entries(&entries, NULL, info.outf, info.options);
	while (dirs)
	{
		ft_printf("%s:\n", dirs->path);
		if (!(dirp = opendir(dirs->path)))
		{
			ft_perror(dirs->name);
			lstdel_head(&dirs);
		}
		else
		{
			btotal = 0;
			tmp = NULL;
			while ((de = readdir(dirp)) != NULL)
			{
				if (display_entry(de->d_name, info.options))
				{
					fp = init_node(dirs, de);
					lstinsert(&entries, fp, info);
					btotal += fp->sbuf.st_blocks;
				}
			}
			lstdel_head(&dirs);
			if (info.options & LONG_LIST && entries)
				ft_printf("total %llu\n", btotal);
			display_entries(&entries, &tmp, info.outf, info.options);
			add_subdirs_to_dirs(&dirs, &tmp);
			if (dirs)
				ft_putchar('\n');
			if (closedir(dirp) == -1)
				ft_perror(dirs->path);
		}
	}
}
