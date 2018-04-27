/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abeauvoi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/09 02:28:45 by abeauvoi          #+#    #+#             */
/*   Updated: 2018/04/27 06:29:24 by abeauvoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "ft_ls.h"

static bool		display_entry(const char *arg, t_ls_opts options)
{
	if (*arg == '.' && (!(options & (ALL | ALMOST_ALL))
				|| ((options & ALMOST_ALL)
						&& (arg[1] == 0 || (arg[1] == '.' && arg[2] == 0)))))
		return (false);
	return (true);
}

static inline void	display_entries(t_fileinfo **list, t_ls_opts options,
		void (*outf)(t_fileinfo *))
{
	while (*list)
	{
		if (display_entry((*list)->name, options))
			outf(*list);
		lstpop(list);
	}
}

void				test(t_ls info, t_fileinfo *entries, t_fileinfo *dirs)
{
	DIR				*dirp;
	struct dirent	*de;
	t_fileinfo		*fp;
	size_t			btotal;

	display_entries(&entries, info.options, info.outf);
	while (dirs)
	{
		if (info.nb_dirs > 1)
			ft_printf("%s:\n", dirs->name);
		if (!(dirp = opendir(dirs->name)))
			ft_perror(dirs->name);
		else
		{
			btotal = 0;
			while ((de = readdir(dirp)) != NULL)
			{
				fp = init_node(dirs, de);
				if (display_entry(fp->name, info.options))
					btotal += fp->sbuf.st_blocks;
				lstinsert(&entries, fp, info.options, info.cmpf);
			}
			if (info.options & LONG_LIST)
				ft_printf("total %llu\n", btotal);
			display_entries(&entries, info.options, info.outf);
			if (dirs->next != NULL)
				ft_putchar('\n');
		}
		lstpop(&dirs);
	}
}
