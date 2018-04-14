/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abeauvoi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/09 02:28:45 by abeauvoi          #+#    #+#             */
/*   Updated: 2018/04/14 01:02:53 by abeauvoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <dirent.h>
#include <stdio.h>
#include <stdlib.h>
#include "ft_ls.h"

static t_bool	display_entry(const char *arg, t_ls_opts options)
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

void			test(t_ls info, t_fileinfo *entries, t_fileinfo *dirs)
{
	DIR				*dirp;
	struct dirent	*de;
	t_fileinfo		*fp;

	display_entries(&entries, info.options, info.outf);
	while (dirs)
	{
		dirp = opendir(dirs->name);
		while ((de = readdir(dirp)) != NULL)
		{
			fp = lstnew();
			lstinsert(&entries, fp, info.options);
		}
		display_entries(&entries, info.options, info.outf);
		lstpop(&dirs);
		dirs = dirs->next;
	}
}
