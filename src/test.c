/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abeauvoi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/09 02:28:45 by abeauvoi          #+#    #+#             */
/*   Updated: 2018/04/09 07:13:41 by abeauvoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <dirent.h>
#include <stdio.h>
#include <stdlib.h>
#include "ft_ls.h"

t_bool	display_entry(const char *arg, t_ls_opts options)
{
	if (*arg == '.' && (!(options & (ALL | ALMOST_ALL))
				|| ((options & ALMOST_ALL)
						&& (arg[1] == 0 || (arg[1] == '.' && arg[2] == 0)))))
		return (FALSE);
	return (TRUE);
}

void	test(const char *const *argv, t_ls info)
{
	DIR				*dirp;
	struct dirent	*dp;
	const char		*tmp;

	while (*argv)
	{
		dirp = opendir(*argv);
		if (dirp == NULL)
		{
			ft_perror(*argv);
			++argv;
			continue ;
		}
		while ((dp = readdir(dirp)) != NULL)
		{
			if (display_entry(dp->d_name, info.options))
			{
				tmp = ft_strdup(dp->d_name);
				info.outf(tmp);
				free((void*)tmp);
				tmp = NULL;
			}
		}
		if (closedir(dirp) == -1)
			perror("ft_ls: ");
		++argv;
	}
}
