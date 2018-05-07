/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_argv.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abeauvoi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/08 22:42:57 by abeauvoi          #+#    #+#             */
/*   Updated: 2018/05/07 05:03:35 by abeauvoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/types.h>
#include "ft_ls.h"
/*
** SIZE_SORT cancels TIME_SORT but not the other way around, it is handled
** separately.
*/

static const uint32_t	g_masks[OPTIONS] = {DISPLAY_MASK, FILETYPE_INDICATOR, 
	SIZE_SORT, RECURSIVE, DISPLAY_MASK, PRINT_INODE, LONG_LIST, REVERSE,
	PRINT_BLOCKS, MODIF_SORT};

static void		parse_one_arg(const char *arg, t_ls_opts *options)
{
	size_t		optind;
	const char	*tmp;

	++arg;
	while (*arg)
	{
		if ((tmp = ft_strchr(FT_LS_OPTIONS, *arg)) != NULL)
		{
			optind = tmp - FT_LS_OPTIONS;
			*options |= (1 << optind);
			*options ^= *options & (g_masks[optind] - (1 << optind));
		}
		else
			print_error_and_exit(ERR_FMT_A, FT_LS_INVALID_OPT, arg);
		++arg;
	}
}

size_t			parse_options(const char *const *argv, t_ls_opts *options)
{
	size_t		index;

	index = 1;
	while (argv[index] && argv[index][0] == '-')
	{
		parse_one_arg((const char*)argv[index], options);
		++index;
	}
	return (index);
}

void			insert_command_line_args(const char *const *argv,
		t_ls *info)
{
	struct stat	sbuf;
	t_fileinfo	*new;

	while (*argv)
	{
		++info->nb_args;
		if (lstat(*argv++, &sbuf) == -1)
		{
			ft_perror(argv[-1], ft_strlen(argv[-1]), info);
			continue ;
		}
		new = lstnew();
		if (!(new->name = ft_strdup(argv[-1]))
				|| !(new->path = ft_strdup(new->name)))
			perror_and_exit();
		new->namlen = ft_strlen(argv[-1]);
		new->pathlen = new->namlen;
		new->stat_ok = 1;
		new->sbuf = sbuf;
		new->filetype = get_filetype(sbuf.st_mode);
		if (S_ISDIR(sbuf.st_mode))
			lstpush(&info->dirs, new);
		else
			lstpush(&info->entries, new);
	}
}
