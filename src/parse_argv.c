/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_argv.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abeauvoi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/08 22:42:57 by abeauvoi          #+#    #+#             */
/*   Updated: 2018/04/09 09:49:53 by abeauvoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

static const uint32_t	g_masks[OPTIONS] = {DISPLAY_MASK, RECURSIVE,
	DISPLAY_MASK, LONG_LIST, SORT_MASK, SORT_MASK};

void				parse_argv(const char *const *argv, uint64_t *flags)
{
	char		*tmp;
	uint8_t		optind;
	char		*arg;
	
	while (*argv)
	{
		arg = (char*)*argv;
		if (arg[0] == '-')
		{
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
		++argv;
	}
}

static inline void	swap_str(const char **s1, const char **s2)
{
	const char	*s;

	s = *s1;
	*s1 = *s2;
	*s2 = s;
}

void				sort_argv(const char **argv)
{
	uint32_t	nonopt_index;
	uint32_t	start_index;

	start_index = 0;
	while (argv[start_index])
	{
		if (argv[start_index][0] != '-')
		{
			++start_index;
			continue ;
		}
		else
		{
			nonopt_index = start_index;
			while (argv[nonopt_index] && argv[nonopt_index][0] == '-')
				++nonopt_index;
			if (!argv[nonopt_index])
			{
				argv[start_index] = NULL;
				return ;
			}
			swap_str(argv + start_index, argv + nonopt_index);
		}
		++start_index;
	}
}
