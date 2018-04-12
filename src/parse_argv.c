/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_argv.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abeauvoi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/08 22:42:57 by abeauvoi          #+#    #+#             */
/*   Updated: 2018/04/12 06:49:32 by abeauvoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/types.h>
#include <sys/stat.h>
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
		parse_one_arg((const char*)*argv, flags);
		++index;
	}
	return (index);
}

void				insert_args(const char *const *argv, t_ls *info)
{
	struct stat	sbuf;

	if (!*argv)
		info->dirs = lstnew("./", NULL, ft_strlen(*argv), 0);
	else
	{
		while (*argv != NULL)
		{
			lstat(*argv, &sbuf);
			if (S_ISDIR(sbuf.st_mode))
				lstinsert(&info->dirs, lstnew(*argv, NULL, ft_strlen(*argv), 0),
						info->options);
			else
				lstinsert(&info->entries, lstnew(*argv, NULL, ft_strlen(*argv),
							0), info->options);
			++argv;
		}	
	}
}
