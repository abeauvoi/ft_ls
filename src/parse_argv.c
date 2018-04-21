/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_argv.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abeauvoi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/08 22:42:57 by abeauvoi          #+#    #+#             */
/*   Updated: 2018/04/21 01:08:58 by abeauvoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/types.h>
#include <sys/stat.h>
#include <stdio.h>
#include "ft_ls.h"

/*
** SIZE_SORT cancels TIME_SORT but not the other way around, it is handled
** separately.
*/

static const uint32_t	g_masks[OPTIONS] = {DISPLAY_MASK, SIZE_SORT, RECURSIVE,
	DISPLAY_MASK, LONG_LIST, REVERSE, MODIF_SORT};

static inline void	parse_one_arg(const char *arg, t_ls_opts *flags)
{
	size_t	optind;
	const char	*tmp;

	++arg;
	while (*arg)
	{
		if ((tmp = ft_strchr(FT_LS_OPTIONS, *arg)) != NULL)
		{
			optind = tmp - FT_LS_OPTIONS;
			*flags |= (1U << optind);
			*flags ^= *flags & (g_masks[optind] - (1U << optind));
		}
		else
			print_error_and_exit(ERR_FMT_A, FT_LS_INVALID_OPT, arg);
		++arg;
	}
}

size_t				parse_options(const char *const *argv, t_ls_opts *flags)
{
	size_t		index;
	
	index = 1;
	while (argv[index] && argv[index][0] == '-')
	{
		parse_one_arg((const char*)argv[index], flags);
		++index;
	}
	return (!index ? 1 : index);
}

static inline void	if_no_arg(t_ls *info)
{
	struct stat		sbuf;

	if (!info->nb_dirs && info->has_no_arg)
	{
		++info->nb_dirs;
		info->dirs = lstnew();
		info->dirs->stat_ok = stat(".", &sbuf) == 0;
		info->dirs->name = ".";
		info->dirs->filetype = DIRECTORY;
		info->dirs->is_cmd_line_arg = 1;
		info->dirs->namlen = 1;
		info->dirs->sbuf = sbuf;
	}
}

void				insert_command_line_args(const char *const *argv,
		t_ls *info)
{
	struct stat	sbuf;
	t_fileinfo	*new;

	while (*argv)
	{
		if (lstat(*argv, &sbuf) == -1)
			perror("ft_ls: Error");
		else
		{
			++info->nb_dirs;
			new = lstnew();
			if (!(new->name = ft_strdup(*argv)))
				perror_and_exit();
			new->namlen = ft_strlen(*argv);
			new->is_cmd_line_arg = 1;
			new->stat_ok = 1;
			new->sbuf = sbuf;
			new->filetype = get_filetype(sbuf.st_mode);
			if (S_ISDIR(sbuf.st_mode))
				lstinsert(&info->dirs, new, info->options, info->cmpf);
			else
				lstinsert(&info->entries, new, info->options, info->cmpf);
		}
		++argv;
	}
	if_no_arg(info);
}
