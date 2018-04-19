/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abeauvoi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/09 02:28:45 by abeauvoi          #+#    #+#             */
/*   Updated: 2018/04/19 06:21:14 by abeauvoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "ft_ls.h"

static t_bool		display_entry(const char *arg, t_ls_opts options)
{
	if (*arg == '.' && (!(options & (ALL | ALMOST_ALL))
				|| ((options & ALMOST_ALL)
						&& (arg[1] == 0 || (arg[1] == '.' && arg[2] == 0)))))
		return (FALSE);
	return (TRUE);
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
	size_t			tot_blocks;

	display_entries(&entries, info.options, info.outf);
	while (dirs)
	{
		if (info.nb_dirs > 1)
			ft_printf("%s:\n", dirs->name);
		if (!(dirp = opendir(dirs->name)))
			perror("ft_ls:");
		else
		{
			tot_blocks = 0;
			while ((de = readdir(dirp)) != NULL)
			{
				fp = init_node(dirs, de);
				tot_blocks += fp->sbuf.st_blocks;
				lstinsert(&entries, fp, info.options);
			}
			if (info.options & LONG_LIST)
				ft_printf("total %llu\n", tot_blocks);
			display_entries(&entries, info.options, info.outf);
			if (dirs->next != NULL)
				ft_putchar('\n');
		}
		lstpop(&dirs);
	}
}
